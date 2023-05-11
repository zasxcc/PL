// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PLLightFlickerNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API UPLLightFlickerNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_NotifyState)
	FName AttachSockName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_NotifyState)
	FTransform AttachOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_NotifyState)
	float FlickerDurationTime = 10.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_NotifyState)
	float FlickerInterval = 0.2f;;
	
	
};
