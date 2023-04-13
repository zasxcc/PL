// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PLType.h"
#include "GameFramework/Controller.h"
#include "PLAiController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTLIGHT_API APLAiController : public AController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiController)
	class UAIPerceptionComponent* AiPerceptionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	ETeam CharacterTeam = ETeam::ENeutral;


public:
	APLAiController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

	// 팀 등록
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void AssignTeam(ETeam _team);
	
	UFUNCTION()
	void OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus);
};
