// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Game/PLType.h"
#include "PLAiController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTLIGHT_API APLAiController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiController)
	TObjectPtr<class UAIPerceptionComponent> AiPerceptionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_AiController)
	ETeam CharacterTeam = ETeam::ENeutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_AiController)
	TObjectPtr<class APLCharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UCharacterMovementComponent> CharacterMovementComp;

	FRotator SmoothTargetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothFocusInterpSpeed = 30.0f;


public:
	APLAiController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn) override;

	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	// 팀 등록
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void AssignTeam(ETeam _team);

	// Perception Sight Loc and Rot
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;
	


	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
