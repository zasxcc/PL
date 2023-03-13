// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PLAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API UPLAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere,Category=PL)
	bool IsMove = false;

	UPROPERTY(VisibleAnywhere,Category=PL)
	class APLCharacter* OwnerPLCharacter = nullptr;
	
	UPROPERTY(VisibleAnywhere,Category=PL)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere,Category=PL)
	float CharacterSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere,Category=PL)
	float NormalizedSpeed = 0.f;
	
	UPROPERTY(VisibleAnywhere,Category=PL)
	FRotator Rotation = FRotator::ZeroRotator;
	
	UPROPERTY(VisibleAnywhere,Category=PL)
	float Direction = 0.0f;
	
	
public:
	/*BeginPlay*/
	virtual void NativeBeginPlay() override;

	/*Tick*/
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//////*Setter, Getter*/////
	UFUNCTION(BlueprintPure, Category=PL, meta=(BlueprintThreadSafe))
	bool GetIsMove() const
	{
		return IsMove;
	};
	
	UFUNCTION(BlueprintPure, Category=PL, meta=(BlueprintThreadSafe))
	APLCharacter* GetOwnerPLCharacter() const
	{
		return OwnerPLCharacter;
	}
	
	UFUNCTION(BlueprintPure, Category=PL, meta=(BlueprintThreadSafe))
	float GetCharacterSpeed() const
	{
		return CharacterSpeed;
	}

	UFUNCTION(BlueprintPure, Category=PL, meta=(BlueprintThreadSafe))
	float GetNormalizedSpeed() const
	{
		return NormalizedSpeed;
	}
	
	UFUNCTION(BlueprintPure, Category=PL, meta=(BlueprintThreadSafe))
	FVector GetVelocity() const
	{
		return Velocity;
	}

	UFUNCTION(BlueprintPure, Category=PL, meta=(BlueprintThreadSafe))
	FRotator GetRotation() const
	{
		return Rotation;
	}

	UFUNCTION(BlueprintPure, Category=PL, meta=(BlueprintThreadSafe))
	float GetDirection() const
	{
		return Direction;
	}
	////Setter, Getter End/////
	
	
};
