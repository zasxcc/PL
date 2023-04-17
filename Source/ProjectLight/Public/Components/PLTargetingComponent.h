// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PLTargetingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIGHT_API UPLTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPLTargetingComponent();

	UPROPERTY(BlueprintReadWrite, Category=PL_Targeting)
	TObjectPtr<AActor> CurrentTarget;

	UPROPERTY(BlueprintReadWrite, Category=PL_Targeting)
	TObjectPtr<APlayerController> PlayerController;

	// 타겟 가능 오브젝트 타입
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PL_Targeting)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectsToQuery;

	// 타겟 가능 오브젝트
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PL_Targeting)
	TArray<AActor*> AvailableTargetArray;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category=PL_Targeting)
	APlayerController* GetPlayerController();

	// 타겟팅 On/Off
	UFUNCTION(BlueprintCallable, Category=PL_Targeting)
	void ToggleTargeting();

	// CurrentTarget Set
	UFUNCTION(BlueprintCallable, Category=PL_Targeting)
	void SetTarget(AActor* _target);

	// 타겟 가능한 엑터들을 찾아서 조건에 가장 맞는 타겟을 CurrentTarget변수에 Set
	UFUNCTION(BlueprintCallable, Category=PL_Targeting)
	void ActivateTargeting();

	// 타겟 가능한 엑터들을 찾아서 Array에 저장
	UFUNCTION(BlueprintCallable, Category=PL_Targeting)
	void PopulatePotentialTargetsArray();

	// _target과의 각도 반환
	UFUNCTION(BlueprintPure, Category=PL_Targeting)
	float GetTargetDegree(AActor* _target);
};
