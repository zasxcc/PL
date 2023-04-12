// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Game/PLType.h"
#include "PLCharacter.generated.h"




UCLASS()
class PROJECTLIGHT_API APLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APLCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL)
	TMap<FGameplayTag, FPlayActionInfo> ActionInfo;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	TObjectPtr<UPLStatisticComponent> StatisticComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	TObjectPtr<UPLActionManagerComponent> ActionManagerComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	TObjectPtr<UPLCollisionTraceComponent> CollisionTraceComponent;


	
	// 가장 최근에 받은 대미지 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PL)
	FDamageInfo LastDamageInfo;

	// 현재 타겟팅한 적
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PL)
	TObjectPtr<APLCharacter> CurrentTargetCharacter;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category=PL)
	void PlayAction(FGameplayTag _actionTag);

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// CurrentTargetCharacter와의 각도 Return
	UFUNCTION(BlueprintPure, Category=PL)
	float GetAngleToTarget() const;
	
	////////////////////////*Getter, Setter*///////////////////////////

	UFUNCTION(BlueprintPure, Category=PL)
	class UPLStatisticComponent* GetPLStatisticComponent() const
	{
		return StatisticComponent;
	}

	UFUNCTION(BlueprintPure, Category=PL)
	class UPLActionManagerComponent* GetPLActionComponent() const
	{
		return ActionManagerComponent;
	}

	UFUNCTION(BlueprintPure, Category=PL)
	class UPLCollisionTraceComponent* GetPLCollisionComponent() const
	{
		return CollisionTraceComponent;
	}
	
	UFUNCTION(BlueprintPure, Category=PL)
		FDamageInfo GetLastDamageInfo() const
	{
		return LastDamageInfo;
	}

	UFUNCTION(BlueprintPure, Category=PL)
		APLCharacter* GetCurrentTargetCharacter() const
	{
		return CurrentTargetCharacter;
	}
	
	UFUNCTION(BlueprintPure, Category=PL)
	class UPLAnimationInstance* GetPLAnimationInstance() const;

	UFUNCTION(BlueprintCallable, Category=PL)
	void SetLastDamageInfo(FDamageInfo _damageInfo)
	{
		LastDamageInfo = _damageInfo;
	}

	UFUNCTION(BlueprintCallable, Category=PL)
	void SetCurrentTargetCharacter(APLCharacter* _character)
	{
		CurrentTargetCharacter = _character;
	}
	
	//////////////////////////////////////////////////////////////////
	
};
