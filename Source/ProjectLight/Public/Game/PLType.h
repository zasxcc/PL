// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PLType.generated.h"

#define STAT_ATK FGameplayTag::RequestGameplayTag("Stat.ATK")
#define STAT_DEF FGameplayTag::RequestGameplayTag("Stat.DEF")
#define STAT_HP FGameplayTag::RequestGameplayTag("Stat.HP")

//방향 Enum
UENUM(BlueprintType)
enum class EDirection : uint8
{
	EForward  = 0	UMETA(DisplayName = "Forward"),
	EBackward = 1   UMETA(DisplayName = "Backward"),
	ELeft	  = 2	UMETA(DisplayName = "Left"),
	ERight	  = 3	UMETA(DisplayName = "Right"),
};

//상태 Enum
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	EIdle = 0		UMETA(DisplayName = "Idle"),
	EPatrol = 1		UMETA(DisplayName = "Patrol"),
	ECombat = 2		UMETA(DisplayName = "Combat"),
	EGroggy = 3		UMETA(DisplayName = "Groggy"),
	EDead	= 4		UMETA(DisplayName = "Dead"),
};


//스텟 관련 상세 구조체
USTRUCT(BlueprintType)
struct FPLStatDetail : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 스텟의 최댓값, -1이라면 최댓값이 없음
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	float MaxValue = 500.0f;

	// 스텟의 현재 값
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	float Value = MaxValue;

	// 리젠되는 값인가
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	bool IsRegenValue = true;

	// 소모시 리젠 딜레이
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL, meta=(EditCondition = "IsRegenValue"))
	float RegenDelay = 1.0f;

	// 현재 리젠 딜레이 값
	UPROPERTY()
	float CurrentRegenDelay = RegenDelay;

	// 초당 리젠 값
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL, meta=(EditCondition = "IsRegenValue"))
	float RegenValue = 5.0f;
	
};

//스텟 관련 구조체
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

// 캐릭터 액션 관련 구조체
USTRUCT(BlueprintType)
struct FPlayActionInfo 
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	TObjectPtr<class UAnimMontage> PlayMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = PL)
	TObjectPtr<class UPLActionBase> PlayAction = nullptr;
};

// 대미지 정보
USTRUCT(BlueprintType)
struct FDamageInfo : public FTableRowBase
{
	GENERATED_BODY()
public:

	FDamageInfo() :
	Damage(0.0f),
	ATK_Ratio(1.0f),
	DamageCauser(nullptr),
	HitLoc(FVector::Zero())
	{}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PL_DamageInfo)
	float Damage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PL_DamageInfo)
	float ATK_Ratio = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = PL_DamageInfo)
	TObjectPtr<AActor> DamageCauser = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = PL_DamageInfo)
	FVector HitLoc = FVector::Zero();
};

//콜리전 관련 구조체
USTRUCT(BlueprintType)
struct FCollisionTraceInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	//콜리전을 만들 소켓 이름 1
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Collision)
	FName StartSock;

	//콜리전을 만들 소켓 이름 2
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Collision)
	FName EndSock;

	//콜리전 크기
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Collision)
	float CollisionSize = 50.0f;

	//콜리전 Offset
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Collision)
	FTransform CollisionOffset;

	//콜리전 채널
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PL_Collision)
	TArray<TEnumAsByte<ECollisionChannel>> CollisionChannels;

	//콜리전 활성화 여부
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PL_Collision)
	bool bIsActivateCollision = false;

	//대미지 정보
	UPROPERTY(BlueprintReadWrite, Category = PL_Collision)
	FDamageInfo DamageInfo;
};

// 콜리전 디텍팅 관련 구조체
USTRUCT(BlueprintType)
struct FHitActors  : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PL_Collision)
	TArray<TObjectPtr<AActor>> AlreadyHitActors;
};


USTRUCT(BlueprintType)
struct FAiCharacterSkillInfo : public  FTableRowBase
{
	GENERATED_BODY()
public:
	FAiCharacterSkillInfo()
	{}

	// 스킬 사용 정보
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacterSkillInfo)
	FPlayActionInfo PlayMontageAndAction;

	// 필요한 자원
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacterSkillInfo)
	float NeedResource = 0;

	// 스킬 사용에 필요한 거리
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacterSkillInfo)
	float ActivateSkillDistance = 1000.0f;

	// 스킬 사용에 필요한 각도
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacterSkillInfo)
	float ActivateSKillAngle = 90.0f;
	
	// 스킬 쿨타임
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacterSkillInfo)
	float SkillColdTime = 10.0f;

	// 스킬 사용 후 쿨타임까지 흐른 시간
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_AiCharacterSkillInfo)
	float CurrentSkillColdTime = SkillColdTime;


};
