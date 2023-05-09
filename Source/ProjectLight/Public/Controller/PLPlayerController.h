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

private:
	UPROPERTY()
	TObjectPtr<class APLPlayerCharacter> PlayerCharacter;

protected:
	UPROPERTY( BlueprintReadWrite, Category = PL_Character)
	bool TurnRight = false;

	UPROPERTY( BlueprintReadWrite, Category = PL_Character)
	bool TurnLeft = false;
	
	UPROPERTY( BlueprintReadWrite, Category = PL_Character)
	bool EnableAttack = true;

	UPROPERTY( BlueprintReadWrite, Category = PL_Character)
	bool EnableGuard = true;

	UPROPERTY( BlueprintReadWrite, Category = PL_Character)
	bool EnableDodge = true;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	ETeam CharacterTeam = ETeam::ENeutral;


public:
	APLPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void TurnInPlace();

	// 팀 등록
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void AssignTeam(ETeam _team);

	/////// Getter, Setter //////
	UFUNCTION(BlueprintPure, Category=PL_Character)
	bool GetEnableAttack() const
	{
		return EnableAttack;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
	bool GetEnableGuard() const
	{
		return EnableGuard;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
	bool GetEnableDodge() const
	{
		return EnableDodge;
	}
	
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetEnableAttack(bool _isEnable)
	{
		EnableAttack = _isEnable;
	}

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetEnableGuard(bool _isEnable)
	{
		EnableGuard = _isEnable;
	}

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetEnableDodge(bool _isEnable)
	{
		EnableDodge = _isEnable;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
	class APLPlayerCharacter* GetPLPlayerCharacter();
	//////////////////////////////
};
