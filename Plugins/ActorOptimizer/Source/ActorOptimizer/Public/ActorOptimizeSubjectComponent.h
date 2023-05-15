// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorOptimizeSubjectComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPreDespawn, UOptimizeData*, Data );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPostSpawned, UOptimizeData*, Data );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTOROPTIMIZER_API UActorOptimizeSubjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorOptimizeSubjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PostSpawnEvent(class UOptimizeData* _data);

	UFUNCTION()
	void PreDespawnEvent(class UActorOptimizeWorldSubsystem* _actorOptimizeSubsystem);
	
public:
	// 디스폰될 때의 이벤트
	UPROPERTY( BlueprintAssignable, Category = Events )
	FOnPreDespawn OnPreDespawn;

	// 스폰될때 의 이벤트
	UPROPERTY( BlueprintAssignable, Category = Events )
	FOnPostSpawned OnPostSpawned;
	
	// 스폰, 디스폰 될 거리 Override, 기본은 4000.0f
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=ActorOptimize)
	float OverrideDespawnDistance = 4000.0f;

	// 데이터 유지를 위한 데이터 저장 클래스
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = ActorOptimize, SaveGame)
	TSubclassOf<class UOptimizeData> DataClass;

	UPROPERTY()
	class UOptimizeData* SpawnData;
		
};
