// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "PLAiController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTLIGHT_API APLAiController : public AController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiController)
	class UAIPerceptionComponent* AiPerceptionComp;

public:
	APLAiController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
};
