// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PLCharacter.h"
#include "Controller/PLPlayerController.h"
#include "PLPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API APLPlayerCharacter : public APLCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<class UCameraComponent> CameraComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<class UPLTargetingComponent> TargetingComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<class USpotLightComponent> SpotLightComponent;

	
public:

	APLPlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void DeadEvent() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void TriggerSkill(FGameplayTag _triggerSkillTag);
	
	UFUNCTION(BlueprintPure, Category=PL)
	UCameraComponent* GetCameraComp() const
	{
		return CameraComp;
	}

	UFUNCTION(BlueprintPure, Category=PL)
	USpringArmComponent* GetSpringArmComp() const
	{
		return SpringArmComp;
	}
	UFUNCTION(BlueprintPure, Category=PL)
	class APLPlayerController* GetPLPlayerController() 
	{
		return Cast<APLPlayerController>(GetLocalViewingPlayerController());
	}
	
};
