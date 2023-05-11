#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Game/PLType.h"
#include "PLStatisticComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIGHT_API UPLStatisticComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPLStatisticComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//캐릭터 스텟 [초기값]
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Stat)
	TMap<FGameplayTag,FPLStatDetail> DefaultCharacterStat;

	//캐릭터 스텟 [실제값]
	UPROPERTY(BlueprintReadWrite, Category=PL_Stat)
	TMap<FGameplayTag,FPLStatDetail> CharacterStat;

	//스텟 리젠 이벤트 타이머
	UPROPERTY()
	FTimerHandle StatRegenTimer;

	//스텟 리젠 이벤트 함수
	UFUNCTION()
	void RegenStat();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/////////// Getter Setter ////////////////////
	UFUNCTION(BlueprintPure, Category=PL_Stat)
	FPLStatDetail GetCurrentCharacterStat(FGameplayTag _charStat);
	
	UFUNCTION(BlueprintPure, Category=PL_Stat)
	FPLStatDetail GetDefaultCharacterStat(FGameplayTag _charStat);
	///////////////////////////////////////////

	//대미지 
	UFUNCTION(BlueprintCallable, Category=PL_Stat)
	void ApplyDamage(float _damage);

	//죽었을 때, 이벤트
	UFUNCTION(BlueprintCallable, Category=PL_Stat)
	void DeadEvent();

	//대미지 계산
	UFUNCTION(BlueprintCallable, Category=PL_Stat)
	float CalculateDamage(FDamageInfo _damageInfo, UPLStatisticComponent* _dealerStaticComp);

	//스텟 수정
	UFUNCTION(BlueprintCallable, Category=PL_Stat)
	void ModifyStat(FGameplayTag _modifyStat, float _addValue, bool _applyRegenDelay);

	//스텟 초기화
	UFUNCTION(BlueprintCallable, Category=PL)
	void InitStat();

	

		
};

