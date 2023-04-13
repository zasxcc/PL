// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PLCharacter.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "PLAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API APLAICharacter : public APLCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacter)
	UAIPerceptionStimuliSourceComponent* AiPerceptionStimuliSourceComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacter)
	TArray<FAiCharacterSkillInfo> SkillInfo;

private:
	// 스킬 관련 타이머
	UPROPERTY()
	FTimerHandle AiSkillTimerHandle;

public:
	APLAICharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// 스킬 관련 타이머 함수
	UFUNCTION()
	void UpdateSkill();

	// 스킬 쿨타임 계산 [초당]
	UFUNCTION()
	void CalculateSkillColdTime();


	UFUNCTION(BlueprintPure, Category=PL_AiCharacter)
	float GetDistanceFromCurrentTarget() const;

	
};
