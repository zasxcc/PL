// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PLActionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class PROJECTLIGHT_API UPLActionBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category=PL)
	class APLCharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadWrite, Category=PL)
	UAnimMontage* PlayMontage;

public:
	/*Called when the action is successfully triggered*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	void OnActionStarted();
	virtual void OnActionStarted_Implementation();

	/*Called when the action is finished.*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	void OnActionEnded();
	virtual void OnActionEnded_Implementation();

	/*Called every frame if the ActionsManagerComponent of this character has bCanTick set to true*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	void OnTick(float DeltaTime);
	virtual void OnTick_Implementation(float DeltaTime);

	/*Implement this to select the name of the montage section that should be played when executing this action */
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	FName GetMontageSectionName();
	virtual FName GetMontageSectionName_Implementation();
};
