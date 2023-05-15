// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorOptimizeWorldSubsystem.h"

#include "OptimizeData.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UActorOptimizeWorldSubsystem::UActorOptimizeWorldSubsystem()
{
	
}

void UActorOptimizeWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(OptimizeTimerHandle, this, &UActorOptimizeWorldSubsystem::UpdateActorOptimize, 0.2f, true);
	}
}

void UActorOptimizeWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
}

void UActorOptimizeWorldSubsystem::AddSpawnedSubjectArray(AActor* _spawnActor, float _overrideDespawnDistance)
{
	FSpawnedSubjectInfo _spawnSubjectInfo;
	_spawnSubjectInfo.SpawnedActor = _spawnActor;
	_spawnSubjectInfo.DespawnDistance = _overrideDespawnDistance;
	
	SpawnedSubjectArray.Add(_spawnSubjectInfo);
}

void UActorOptimizeWorldSubsystem::AddDespawnedSubjectArray(TSubclassOf<AActor> _despawnedClass,
	FTransform _tr,  float _overrideSpawnDisntance, UOptimizeData* _data)
{
	FDespawnedSubjectInfo _despawnSubjectInfo;
	_despawnSubjectInfo.SpawnClass = _despawnedClass;
	_despawnSubjectInfo.SpawnDistance = _overrideSpawnDisntance;
	_despawnSubjectInfo.DespawnedTransform = _tr;
	_despawnSubjectInfo.Data = _data;
	
	DespawnedSubjectArray.Add(_despawnSubjectInfo);
}

void UActorOptimizeWorldSubsystem::UpdateActorOptimize()
{
	if(GetPlayerChar())
	{
		// 스폰된 오브젝트들 플레이어와의 거리검사를 통해 충분히 멀다면, Destroy 및 DespawnedSubjectArray에 추가
		for(int i =  0; i <SpawnedSubjectArray.Num(); ++i)
		{
			if(IsValid(SpawnedSubjectArray[i].SpawnedActor))
			{
				// 플레이어와의 거리 
				const float _distanceToPlayer = UKismetMathLibrary::Vector_Distance(
					SpawnedSubjectArray[i].SpawnedActor->GetActorLocation(),
					GetPlayerChar()->GetActorLocation());

				// 플레이어와의 거리가 DesapwnDistance보다 멀다면
				if(_distanceToPlayer > SpawnedSubjectArray[i].DespawnDistance)
				{
					UActorOptimizeSubjectComponent* _subjectComp = SpawnedSubjectArray[i].SpawnedActor->FindComponentByClass<UActorOptimizeSubjectComponent>();
					if(IsValid(_subjectComp))
					{
						// 디스폰된 엑터의 데이터 유지를 위한 이벤트
						_subjectComp->PreDespawnEvent(this);
					}

					// SpawnedSubjectArray 배열에 추가
					AddDespawnedSubjectArray(SpawnedSubjectArray[i].SpawnedActor->GetClass(),
										  SpawnedSubjectArray[i].SpawnedActor->GetActorTransform(),
											 SpawnedSubjectArray[i].DespawnDistance,
											 _subjectComp->SpawnData);
					// 엑터 삭제
					SpawnedSubjectArray[i].SpawnedActor->Destroy();
					SpawnedSubjectArray.RemoveAt(i);
				}
			}
		}

		// 디스폰된 오브젝트들이 플레이어와의 거리가 충분히 가깝다면, Spawn 및 SpawnedSubjectArray에 추가
		for(int i = 0; i <  DespawnedSubjectArray.Num(); ++i)
		{
			const float _distanceToPlayer = UKismetMathLibrary::Vector_Distance(
				DespawnedSubjectArray[i].DespawnedTransform.GetLocation(),
				GetPlayerChar()->GetActorLocation());
			
			if(_distanceToPlayer < DespawnedSubjectArray[i].SpawnDistance)
			{
				FActorSpawnParameters _spawnParams;
				_spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
				AActor* _spawnedActor = GetWorld()->SpawnActor(DespawnedSubjectArray[i].SpawnClass, &DespawnedSubjectArray[i].DespawnedTransform, _spawnParams );

				if(IsValid(_spawnedActor))
				{
					UActorOptimizeSubjectComponent* _subjectComp = _spawnedActor->FindComponentByClass<UActorOptimizeSubjectComponent>();
					if(IsValid(_subjectComp))
					{
						// 스폰된 엑터의 데이터 유지를 위한 이벤트
						if(DespawnedSubjectArray[i].Data)
						{
							_subjectComp->PostSpawnEvent(DespawnedSubjectArray[i].Data);
					
							// 스폰 디스폰간 데이터 유지를 위해 생성한 Data 오브젝트 삭제
							DespawnedSubjectArray[i].Data->MarkAsGarbage();
							DespawnedSubjectArray[i].Data = nullptr;
						}
						AddSpawnedSubjectArray(_spawnedActor, _subjectComp->OverrideDespawnDistance);
						DespawnedSubjectArray.RemoveAt(i);
					}
				}
			}
		}
	}
}

ACharacter* UActorOptimizeWorldSubsystem::GetPlayerChar()
{
	if(PlayerCharacter == nullptr)
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	}
	return PlayerCharacter;
}
