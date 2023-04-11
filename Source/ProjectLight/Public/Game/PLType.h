// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PLType.generated.h"

//방향 Enum
UENUM(BlueprintType)
enum class EDirection : uint8
{
	EForward = 0	UMETA(DisplayName = "Forward"),
	EBackward = 1   UMETA(DisplayName = "Backward"),
	ELeft = 2		UMETA(DisplayName = "Left"),
	ERight = 3		UMETA(DisplayName = "Right"),
};


//스텟 관련 상세 구조체
USTRUCT(BlueprintType)
struct FPLStatDetail : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	float Value = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	bool IsRegenValue = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL, meta=(EditCondition = "IsRegenValue"))
	float RegenDelay = 1.0f;

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

//플레이어 액션 관련 구조체
USTRUCT(BlueprintType)
struct FPlayActionInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	class UAnimMontage* PlayMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = PL)
	class UPLActionBase* PlayAction = nullptr;
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
};

// 콜리전 디텍팅 관련 구조체
USTRUCT(BlueprintType)
struct FPLHitActors {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = ACM)
	TArray<TObjectPtr<AActor>> AlreadyHitActors;
};