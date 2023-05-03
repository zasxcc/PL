// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PLCharacter.h"
#include "Interface/PLTargetableInterface.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "PLAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API APLAICharacter : public APLCharacter, public IPLTargetableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacter)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> AiPerceptionStimuliSourceComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacter)
	TArray<FAiCharacterSkillInfo> SkillInfo;

protected:
	// 현재 타겟팅한 적
	UPROPERTY(BlueprintReadWrite, Category=PL_Character)
	TObjectPtr<APLCharacter> CurrentTargetCharacter;

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

	UFUNCTION(BlueprintPure, Category=PL_AiCharacter)
	class APLAiController* GetPLAiController() const;
	
	UFUNCTION(BlueprintPure, Category=PL_Character)
	APLCharacter* GetCurrentTargetCharacter() const
	{
		return CurrentTargetCharacter;
	}

	

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetCurrentTargetCharacter(APLCharacter* _character)
	{
		if(_character != nullptr)
			CharacterState = ECharacterState::ECombat;
		
		CurrentTargetCharacter = _character;
	}
	
	// CurrentTargetCharacter와의 각도 Return
	UFUNCTION(BlueprintPure, Category=PL_Character)
	float GetAngleToTarget() const;
	
};
