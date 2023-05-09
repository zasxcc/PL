// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PLTargetableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UPLTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTLIGHT_API IPLTargetableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 플레이어에게 타겟팅 되었을 때 호출 함수
	UFUNCTION()
	virtual void BecomeTargetEvent();

	// 플레이어에게서 타겟팅이 해제되었을 때 호출 함수
	UFUNCTION()
	virtual void BecomeNonTargetEvent();
};
