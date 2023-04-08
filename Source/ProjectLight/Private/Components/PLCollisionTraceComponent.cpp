// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PLCollisionTraceComponent.h"

#include "Character/PLCharacter.h"
#include "Game/PLType.h"
#include "Kismet/KismetSystemLibrary.h"

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
	
	//콜리전 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(CollisionTimerHandle, this, &UPLCollisionTraceComponent::UpdateCollisionTrace, 0.05f, true);
}

void UPLCollisionTraceComponent::StartCollisionTrace(FName _collisionTraceInfoName)
{
	if(CollisionTraceInfo.Contains(_collisionTraceInfoName))
	{
		CollisionTraceInfo[_collisionTraceInfoName].bIsActivateCollision = true;
	}
}

void UPLCollisionTraceComponent::StopCollisionTrace(FName _collisionTraceInfoName)
{
	if(CollisionTraceInfo.Contains(_collisionTraceInfoName))
	{
		CollisionTraceInfo[_collisionTraceInfoName].bIsActivateCollision = false;
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

				// 콜리전이 무시할 엑터 추가
				FCollisionQueryParams Params;
				Params.AddIgnoredActor(_ownerCharacter);
				if(IgnoredActors.Num() > 0)
				{
					Params.AddIgnoredActors(IgnoredActors);
				}
			
				const bool bHit = GetWorld()->SweepSingleByObjectType(_hitRes, _startPos, _endPos, _orientation.Quaternion(), _objectParams,
										FCollisionShape::MakeSphere(CollisionTraceInfo[_collisionTrace.Key].CollisionSize), Params);

				//Debug Sphere
				FHitResult _debugTraceRes;
				UKismetSystemLibrary::SphereTraceSingle(GetWorld(), _startPos, _endPos, CollisionTraceInfo[_collisionTrace.Key].CollisionSize,TraceTypeQuery1, false,
													  IgnoredActors, EDrawDebugTrace::ForDuration, _debugTraceRes, true);
			}
		}
	}
}

FRotator UPLCollisionTraceComponent::GetLineRotation(FVector start, FVector end)
{
	FVector _diff = end - start;
	return _diff.Rotation();
}

