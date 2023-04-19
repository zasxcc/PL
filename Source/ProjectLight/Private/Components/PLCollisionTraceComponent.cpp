// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PLCollisionTraceComponent.h"
#include "Character/PLCharacter.h"
#include "Components/PLStatisticComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/DamageEvents.h"
#include "Game/PLType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
UPLCollisionTraceComponent::UPLCollisionTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPLCollisionTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 콜리전 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(CollisionTimerHandle, this, &UPLCollisionTraceComponent::UpdateCollisionTrace, 0.01f, true);
}

void UPLCollisionTraceComponent::StartCollisionTrace(FName _collisionTraceInfoName,  FDamageInfo _damageInfo)
{
	if(CollisionTraceInfo.Contains(_collisionTraceInfoName))
	{
		// 이미 활성화된 상태라면, 한번 Stop시키고 재활성화
		if(CollisionTraceInfo[_collisionTraceInfoName].bIsActivateCollision == true)
		{
			StopCollisionTrace(_collisionTraceInfoName);
		}
		// 대미지 정보 Set
		CollisionTraceInfo[_collisionTraceInfoName].DamageInfo = _damageInfo;
		if(GetOwner())
		{
			CollisionTraceInfo[_collisionTraceInfoName].DamageInfo.DamageCauser = GetOwner();
		}
		
		// 콜리전 활성화
		CollisionTraceInfo[_collisionTraceInfoName].bIsActivateCollision = true;
	}
}

void UPLCollisionTraceComponent::StopCollisionTrace(FName _collisionTraceInfoName)
{
	if(CollisionTraceInfo.Contains(_collisionTraceInfoName))
	{
		// 콜리전 비활성화
		CollisionTraceInfo[_collisionTraceInfoName].bIsActivateCollision = false;
		CollisionTraceInfo[_collisionTraceInfoName].DamageInfo = FDamageInfo();
		// AlreadyHitActors 초기화
		if(AlreadyHitActors.Contains(_collisionTraceInfoName))
		{
			AlreadyHitActors[_collisionTraceInfoName].AlreadyHitActors.Empty();
			AlreadyHitActors.Remove(_collisionTraceInfoName);
		}
		// IgnoredActors 초기화
		IgnoredActors.Empty();
	}
}

void UPLCollisionTraceComponent::UpdateCollisionTrace()
{
	for(auto& _collisionTrace : CollisionTraceInfo)
	{
		if(CollisionTraceInfo[_collisionTrace.Key].bIsActivateCollision)
		{
			FHitResult _hitRes;
			TObjectPtr<APLCharacter> _ownerCharacter = Cast<APLCharacter>(GetOwner());
			if(IsValid(_ownerCharacter))
			{
				// 콜리전 시작, 끝 위치
				FVector _startPos = _ownerCharacter->GetMesh()->GetSocketLocation( CollisionTraceInfo[_collisionTrace.Key].StartSock);
				FVector _endPos = _ownerCharacter->GetMesh()->GetSocketLocation( CollisionTraceInfo[_collisionTrace.Key].EndSock);

				//콜리전 Orientation
				const FRotator _orientation = GetLineRotation(_startPos, _endPos);

				// 콜리전이 탐색할 채널 추가
				FCollisionObjectQueryParams _objectParams;
				for (ECollisionChannel channel : CollisionTraceInfo[_collisionTrace.Key].CollisionChannels)
				{
					_objectParams.AddObjectTypesToQuery(channel);
				}

				
				FCollisionQueryParams Params;
				// 콜리전이 무시할 엑터 추가
				Params.AddIgnoredActor(_ownerCharacter);

				// 피직스 머테리얼 Return 가능하도록 true
				Params.bReturnPhysicalMaterial = true;
				if(IgnoredActors.Num() > 0)
				{
					Params.AddIgnoredActors(IgnoredActors);
				}

				// SweepSingleByObjectType
				const bool bHit = GetWorld()->SweepSingleByObjectType(_hitRes, _startPos, _endPos, _orientation.Quaternion(), _objectParams,
										FCollisionShape::MakeSphere(CollisionTraceInfo[_collisionTrace.Key].CollisionSize), Params);

				// Draw Debug Sphere
				if(bDisplayDebugSphere)
				{
					FHitResult _debugTraceRes;
					UKismetSystemLibrary::SphereTraceSingle(GetWorld(), _startPos, _endPos, CollisionTraceInfo[_collisionTrace.Key].CollisionSize,TraceTypeQuery1, false,
													  IgnoredActors, EDrawDebugTrace::ForDuration, _debugTraceRes, true);
				}

				// 콜리전에 걸린 엑터들 처리
				if(bHit)
				{
					if(AlreadyHitActors.Contains(_collisionTrace.Key) == false)
					{
						AlreadyHitActors.Add(_collisionTrace.Key);
					}
					AlreadyHitActors[_collisionTrace.Key].AlreadyHitActors.AddUnique(_hitRes.GetActor());
					IgnoredActors.AddUnique(_hitRes.GetActor());

					if(IsValid(_hitRes.GetActor()))
					{
						if(GetOwner())
						{
							FDamageEvent _damageEvent;
							TObjectPtr<UPLStatisticComponent> _hitActorStaticComp = Cast<UPLStatisticComponent>(_hitRes.GetActor()->FindComponentByClass<UPLStatisticComponent>());
							if(IsValid(_hitActorStaticComp))
							{
								// HitLocation 
								CollisionTraceInfo[_collisionTrace.Key].DamageInfo.HitLoc = _hitRes.Location;

								// 대미지 계산
								CollisionTraceInfo[_collisionTrace.Key].DamageInfo.Damage = _hitActorStaticComp->CalculateDamage(CollisionTraceInfo[_collisionTrace.Key].DamageInfo, _ownerCharacter->GetPLStatisticComponent());
								
								// 공격당한 엑터가 APLCharacter라면 Set LastDamageInfo 
								if(Cast<APLCharacter>(_hitRes.GetActor()))
								{
									Cast<APLCharacter>(_hitRes.GetActor())->SetLastDamageInfo(CollisionTraceInfo[_collisionTrace.Key].DamageInfo);
								}
							}

							//피직스 머테리얼 SurfaceType에 맞는 파티클과 사운드 재생
							if(CollisionTraceInfo[_collisionTrace.Key].DamageInfo.PlayEffectAndSound.Contains(_hitRes.PhysMaterial.Get()->SurfaceType))
							{
								UNiagaraSystem* _playEffect = CollisionTraceInfo[_collisionTrace.Key].DamageInfo.PlayEffectAndSound[_hitRes.PhysMaterial.Get()->SurfaceType].PlayEffect;
								USoundBase* _playSound = CollisionTraceInfo[_collisionTrace.Key].DamageInfo.PlayEffectAndSound[_hitRes.PhysMaterial.Get()->SurfaceType].PlaySound;
								if(_playEffect)
								{
									UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _playEffect, _hitRes.Location, _hitRes.ImpactNormal.Rotation());
								}
								if(_playSound)
								{
									UGameplayStatics::PlaySoundAtLocation(GetOwner(), _playSound, _hitRes.Location);
								}
							}
							
							//대미지 적용
							_hitRes.GetActor()->TakeDamage(CollisionTraceInfo[_collisionTrace.Key].DamageInfo.Damage, _damageEvent, GetOwner()->GetInstigatorController(),GetOwner());
						}
					}
				}
			}
		}
	}
}

FRotator UPLCollisionTraceComponent::GetLineRotation(FVector start, FVector end)
{
	FVector _diff = end - start;
	return _diff.Rotation();
}

