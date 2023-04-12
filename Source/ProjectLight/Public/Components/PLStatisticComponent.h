#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	FPLStat DefaultCharacterStat;

	//캐릭터 스텟 [실제값]
	UPROPERTY(BlueprintReadWrite, Category=PL)
	FPLStat CharacterStat;

	//스텟 리젠 이벤트 타이머
	UPROPERTY()
	FTimerHandle StatRegenTimer;

	//스텟 리젠 이벤트 함수
	UFUNCTION()
	void RegenStat();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//대미지 
	UFUNCTION(BlueprintCallable, Category=PL)
	void ApplyDamage(float _damage);

	//죽었을 때, 이벤트
	UFUNCTION(BlueprintCallable, Category=PL)
	void DeadEvent();

	//대미지 계산
	UFUNCTION(BlueprintCallable, Category=PL)
	float CalculateDamage(FDamageInfo _damageInfo, UPLStatisticComponent* _dealerStaticComp);

	//스텟 초기화
	UFUNCTION(BlueprintCallable, Category=PL)
	void InitStat();

	

		
};

