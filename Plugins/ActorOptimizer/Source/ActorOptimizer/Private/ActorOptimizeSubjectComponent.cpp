// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorOptimizeSubjectComponent.h"

#include "ActorOptimizeWorldSubsystem.h"
#include "OptimizeData.h"
#include "Character/PLCharacter.h"

// Sets default values for this component's properties
UActorOptimizeSubjectComponent::UActorOptimizeSubjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorOptimizeSubjectComponent::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld())
	{
		UActorOptimizeWorldSubsystem* _optimizeSubsystem = GetWorld()->GetSubsystem<UActorOptimizeWorldSubsystem>();
		if(_optimizeSubsystem)
		{
			// Optimize 시스템이 관리하도록 배열에 추가
			_optimizeSubsystem->AddSpawnedSubjectArray(GetOwner(), OverrideDespawnDistance);
			if(SpawnData == nullptr)
			{
				SpawnData = NewObject<UOptimizeData>( _optimizeSubsystem, DataClass );
			}
		}
	}
}


// Called every frame
void UActorOptimizeSubjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorOptimizeSubjectComponent::PostSpawnEvent(UOptimizeData* _data)
{
	// 생성시, 데이터 유지를 위해 
	OnPostSpawned.Broadcast(_data);
	// Set SpawnData
	SpawnData = _data;
	// 스폰한 엑터가 폰이라면, 컨트롤러 스폰 및 소유
	if(Cast<APawn>(GetOwner()))
	{
		Cast<APawn>(GetOwner())->SpawnDefaultController();
	}
	
}

void UActorOptimizeSubjectComponent::PreDespawnEvent(UActorOptimizeWorldSubsystem* _actorOptimizeSubsystem)
{
	if( DataClass )
	{
		// 삭제될 때, 데이터 유지를 위해 데이터 오브젝트 생성
		UOptimizeData* _saveData = nullptr;
		_saveData = NewObject<UOptimizeData>( _actorOptimizeSubsystem, DataClass );
		SpawnData = _saveData;

		// 생성한 데이터를 인자값으로 델리게이트 Broadcast
		OnPreDespawn.Broadcast(SpawnData);
	}
}


