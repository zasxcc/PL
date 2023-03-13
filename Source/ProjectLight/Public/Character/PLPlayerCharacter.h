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
	
private:
	UPROPERTY(VisibleAnywhere, Category=PL)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category=PL)
	class USpringArmComponent* SpringArmComp;
	
public:

	APLPlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
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
