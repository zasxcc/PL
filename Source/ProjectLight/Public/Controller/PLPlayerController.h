// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PLType.h"
#include "GameFramework/PlayerController.h"
#include "PLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API APLPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	ETeam CharacterTeam = ETeam::ENeutral;
	
public:
	APLPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	// 팀 등록
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void AssignTeam(ETeam _team);
};
