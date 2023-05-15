// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorOptimizeSubjectComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "ActorOptimizeWorldSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FDespawnedSubjectInfo
{
	GENERATED_BODY()
public:
	FDespawnedSubjectInfo(){}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=ActorOptimize)
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=ActorOptimize)
	FTransform DespawnedTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=ActorOptimize)
	float SpawnDistance = 4000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=ActorOptimize)
	class UOptimizeData* Data = nullptr;
};

USTRUCT(BlueprintType)
struct FSpawnedSubjectInfo
{
	GENERATED_BODY()
public:
	FSpawnedSubjectInfo(){}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=ActorOptimize)
	AActor* SpawnedActor = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=ActorOptimize)
	float DespawnDistance = 4000.0f;
};


UCLASS()
class ACTOROPTIMIZER_API UActorOptimizeWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	UActorOptimizeWorldSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// SpawnedSubjectArray에 스폰된 엑터 추가
	UFUNCTION()
	void AddSpawnedSubjectArray(AActor* _spawnActor, float _overrideDespawnDistance);

	// DespawnedSubjectArray에 디스폰된 엑터 추가
	UFUNCTION()
	void AddDespawnedSubjectArray(TSubclassOf<AActor> _despawnedClass, FTransform _tr,
		float _overrideSpawnDisntance, UOptimizeData* _data);

private:
	UFUNCTION()
	void UpdateActorOptimize();

	UFUNCTION(BlueprintPure)
	ACharacter* GetPlayerChar();

private:
	UPROPERTY()
	FTimerHandle OptimizeTimerHandle;

	UPROPERTY()
	ACharacter* PlayerCharacter;

protected:
	UPROPERTY(BlueprintReadWrite, Category=ActorOptimize)
	TArray<FDespawnedSubjectInfo> DespawnedSubjectArray;

	UPROPERTY(BlueprintReadWrite, Category=ActorOptimize)
	TArray<FSpawnedSubjectInfo> SpawnedSubjectArray;

};
