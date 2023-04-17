// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/PLType.h"
#include "PLCollisionTraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIGHT_API UPLCollisionTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPLCollisionTraceComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Collision)
	TMap<FName,FCollisionTraceInfo> CollisionTraceInfo;

	UPROPERTY(BlueprintReadOnly, Category = PL_Collision)
	TArray<TObjectPtr<AActor>> IgnoredActors;

	UPROPERTY()
	FTimerHandle CollisionTimerHandle;

	UPROPERTY()
	TMap<FName, FHitActors> AlreadyHitActors;

	UPROPERTY(EditAnywhere, Category=PL_Collision, BlueprintReadWrite)
	bool bDisplayDebugSphere = false;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//콜리전 스타트
	UFUNCTION(BlueprintCallable, Category=PL_Collision)
	void StartCollisionTrace(FName _collisionTraceInfoName, FDamageInfo _damageInfo);

	//콜리전 스탑
	UFUNCTION(BlueprintCallable, Category=PL_Collision)
	void StopCollisionTrace(FName _collisionTraceInfoName);

	//콜리전 생성관련 업데이트
	UFUNCTION(BlueprintCallable, Category=PL_Collision)
	void UpdateCollisionTrace();

	FRotator GetLineRotation(FVector start, FVector end);
		
};
