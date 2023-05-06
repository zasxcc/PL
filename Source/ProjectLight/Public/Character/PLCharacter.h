// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Game/PLType.h"
#include "PLCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateReceiveDamage_OneParam, APLCharacter*, DamageDealer);


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

	// 대미지 입을시 이벤트 델리게이트	
	UPROPERTY(BlueprintAssignable, Category = PL_Character)
	FDelegateReceiveDamage_OneParam DelegateReceiveDamage_OneParam;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<UPLStatisticComponent> StatisticComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<UPLActionManagerComponent> ActionManagerComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Character)
	TObjectPtr<UPLCollisionTraceComponent> CollisionTraceComponent;
	
	
	
	// 무적 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	bool IsImmortality = false;

	// 패링 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	bool IsParry = false;

	// 가드 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	bool IsGuard = false;

	// 가장 최근에 받은 대미지 정보
	UPROPERTY(BlueprintReadWrite, Category=PL_Character)
	FDamageInfo LastDamageInfo;



	
	UPROPERTY()
	FTimerHandle ParryTimerHandle;

public:
	//방어시의 이펙트와 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	FEffectAndSound GuardParticleAndSound;

	//패링시의 이펙트와 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL_Character)
	FEffectAndSound ParryParticleAndSound;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 액션 실행
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void PlayAction(FGameplayTag _actionTag);
	
	// 죽었을 때 이벤트
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	virtual void DeadEvent();

	// 가드 시작 이벤트
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void StartGuard();

	// 가드 스탑 이벤트
	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void StopGuard();

	// 대미지 받을시 이벤트 (Delegate 바인딩)
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	void DamageReceiveEvent(class APLCharacter* _dealer);
	virtual void DamageReceiveEvent_Implementation(class APLCharacter* _dealer);
	

	// 대미지 받을시 이벤트
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	
	// min <= rand <= max 랜덤 값 리턴
	UFUNCTION(BlueprintPure, Category=PL_Character)
	static int GetRandomInt(int _min, int _max);

	UFUNCTION(BlueprintPure, Category=PL_Character)
	float GetCurrentStatPercent(FGameplayTag _currentStat) const;
	
	
	//////////////////////// Getter, Setter ///////////////////////////

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
	bool GetIsImmortality() const
	{
		return IsImmortality;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
	bool GetIsParry() const
	{
		return IsParry;
	}

	UFUNCTION(BlueprintPure, Category=PL_Character)
	bool GetIsGuard() const
	{
		return IsGuard;
	}
	
	UFUNCTION(BlueprintPure, Category=PL_Character)
	class UPLAnimationInstance* GetPLAnimationInstance() const;

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetLastDamageInfo(FDamageInfo _damageInfo)
	{
		LastDamageInfo = _damageInfo;
	}

	

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetIsImmortality(bool _isImmortal)
	{
		IsImmortality = _isImmortal;
	}

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetIsGuard(bool _isGuard)
	{
		IsGuard = _isGuard;
	}

	UFUNCTION(BlueprintCallable, Category=PL_Character)
	void SetIsParry(bool _isParry)
	{
		IsParry = _isParry;
	}
	
	//////////////////////////////////////////////////////////////////
	
};
