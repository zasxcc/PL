// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/PLActionBase.h"
#include "PLGuardAction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API UPLGuardAction : public UPLActionBase
{
	GENERATED_BODY()
	
public:
    virtual void OnActionStarted_Implementation() override;
    virtual void OnActionEnded_Implementation() override;
    virtual void OnTick_Implementation(float DeltaTime) override;
};
