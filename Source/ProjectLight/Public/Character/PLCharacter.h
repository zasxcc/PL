// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Game/PLType.h"
#include "PLCharacter.generated.h"




UCLASS()
class PROJECTLIGHT_API APLCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APLCharacter();

	//캐릭터 액션 Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	TMap<FGameplayTag, FPlayActionInfo> ActionInfo;

	//현재 캐릭터 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	ECharacterState CharacterState = ECharacterState::EIdle;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<UPLStatisticComponent> StatisticComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<UPLActionManagerComponent> ActionManagerComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<UPLCollisionTraceComponent> CollisionTraceComponent;
	
	// 가장 최근에 받은 대미지 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PL_Character)
	FDamageInfo LastDamageInfo;

	// 현재 타겟팅한 적
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PL_Character)
	TObjectPtr<APLCharacter> CurrentTargetCharacter;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void PlayAction(FGameplayTag _actionTag);

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// CurrentTargetCharacter와의 각도 Return
	UFUNCTION(BlueprintPure, Category=PL_Character)
	float GetAngleToTarget() const;
	
	// min <= rand <= max 랜덤 값 리턴
	UFUNCTION(BlueprintPure, Category=PL_Character)
	static int GetRandomInt(int _min, int _max);
	
	
	////////////////////////*Getter, Setter*///////////////////////////

	UFUNCTION(BlueprintPure, Category=PL_Character)
	class UPLStatisticComponent* GetPLStatisticComponent() const
	{
		return StatisticComponent;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
	class UPLActionManagerComponent* GetPLActionComponent() const
	{
		return ActionManagerComponent;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
	class UPLCollisionTraceComponent* GetPLCollisionComponent() const
	{
		return CollisionTraceComponent;
	}
	
	UFUNCTION(BlueprintPure, Category=PL_Character)
		FDamageInfo GetLastDamageInfo() const
	{
		return LastDamageInfo;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
		APLCharacter* GetCurrentTargetCharacter() const
	{
		return CurrentTargetCharacter;
	}
	
	UFUNCTION(BlueprintPure, Category=PL_Character)
	class UPLAnimationInstance* GetPLAnimationInstance() const;

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetLastDamageInfo(FDamageInfo _damageInfo)
	{
		LastDamageInfo = _damageInfo;
	}

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetCurrentTargetCharacter(APLCharacter* _character)
	{
		CurrentTargetCharacter = _character;
	}
	
	//////////////////////////////////////////////////////////////////
	
};
