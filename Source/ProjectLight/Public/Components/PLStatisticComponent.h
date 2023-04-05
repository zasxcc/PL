#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "PLStatisticComponent.generated.h"

USTRUCT(BlueprintType)
struct FPLStatDetail : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	float Value = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	bool IsRegenValue = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	float RegenDelay = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	float RegenValue = 5.0f;
	
};

USTRUCT(BlueprintType)
struct FPLStat : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	FPLStatDetail HP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	FPLStatDetail Stamina;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	FPLStatDetail Resource;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	FPLStatDetail ATK;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	FPLStatDetail DEF;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	float MovementSpeed = 600.0f;
};

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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
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

	//스텟 초기화
	UFUNCTION(BlueprintCallable, Category=PL)
	void InitStat();

		
};

