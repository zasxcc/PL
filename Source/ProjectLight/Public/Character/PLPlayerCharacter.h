// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PLCharacter.h"
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
	
public:

	APLPlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
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
	
	
};
