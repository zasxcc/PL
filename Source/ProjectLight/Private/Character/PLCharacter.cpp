// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLCharacter.h"
#include "Components//PLStatisticComponent.h"
#include "GameplayTagContainer.h"
#include "Animation/PLAnimationInstance.h"
#include "Components/PLCollisionTraceComponent.h"
#include <random>

#include "Action/PLActionBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/PLActionManagerComponent.h"

// Sets default values
APLCharacter::APLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatisticComponent = CreateDefaultSubobject<UPLStatisticComponent>(TEXT("Stat Comp"));
	ActionManagerComponent = CreateDefaultSubobject<UPLActionManagerComponent>(TEXT("Action Comp"));
	CollisionTraceComponent = CreateDefaultSubobject<UPLCollisionTraceComponent>(TEXT("Collision Comp"));
	
}

// Called when the game starts or when spawned
void APLCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 대미지 받을 시 이벤트 바인딩
	DelegateReceiveDamage_OneParam.AddUniqueDynamic(this, &APLCharacter::DamageReceiveEvent);
}

// Called every frame
void APLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APLCharacter::PlayAction(FGameplayTag _actionTag)
{
	if(ActionInfo.Contains(_actionTag))
	{
		// StoredActionInfo에 재생할 Action과 Montage 저장 
		ActionManagerComponent->StoredActionInfo = ActionInfo[_actionTag];

		// ExecuteAction 실행 성공여부 
		const bool _isExecute =  ActionManagerComponent->ExecuteAction(ActionInfo[_actionTag].PlayAction);
		
		if(GetPLActionComponent()->CurrentAction && _isExecute)
		{
			const FName _montageSectionName = GetPLActionComponent()->CurrentAction->GetMontageSectionName();
			PlayAnimMontage(ActionInfo[_actionTag].PlayMontage, 1.0f, _montageSectionName);
		}
	}
}


void APLCharacter::DeadEvent()
{
	// 캐릭터 상태 변경
	CharacterState = ECharacterState::EDead;

	// 무적
	SetIsImmortality(true);
	// 콜리전 
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 중력 Disable
	GetMesh()->SetEnableGravity(false);
	GetCapsuleComponent()->SetEnableGravity(false);

	PlayAction(FGameplayTag::RequestGameplayTag("Action.Common.Dead"));
}

void APLCharacter::StartGuard()
{
	SetIsGuard(true);
	SetIsParry(true);

	PlayAction(FGameplayTag::RequestGameplayTag("Action.Common.Guard"));

	GetWorld()->GetTimerManager().SetTimer(ParryTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 패링 false
			SetIsParry(false);
		
			// 타이머 초기화
			GetWorld()->GetTimerManager().ClearTimer(ParryTimerHandle);
		}), 0.2f, false);
	
}

void APLCharacter::StopGuard()
{
	SetIsGuard(false);
	SetIsParry(false);
	GetWorld()->GetTimerManager().ClearTimer(ParryTimerHandle);;
}


void APLCharacter::DamageReceiveEvent_Implementation(APLCharacter* _dealer)
{
	// 대미지 받을시 이벤트
}

float APLCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 무적이면 Return (대미지 Causer가 CollisionTraceComponent로 대미지를 발생시켰다면, Receiver가 무적일 경우의 처리를 CollisionTraceComponent에서 먼저 처리해버림)
	if(IsImmortality)
		return 0.0f;

	// 대미지가 0이하라면 Return
	if(DamageAmount <= 0.0f)
		return 0.0f;
	
	// 대미지 
	GetPLStatisticComponent()->ApplyDamage(DamageAmount);
	// HitGage 증가
	GetPLStatisticComponent()->ModifyStat(STAT_HitGage, DamageAmount, false);

	// Trigger DeadEvent
	if(GetPLStatisticComponent()->GetCurrentCharacterStat(STAT_HP).Value <= 0.0f)
	{
		DeadEvent();
		return 0.0f;
	}
	
	const float _hitGageMaxValue = GetPLStatisticComponent()->GetCurrentCharacterStat(STAT_HitGage).MaxValue;
	const float _hitGageCurrentValue = GetPLStatisticComponent()->GetCurrentCharacterStat(STAT_HitGage).Value;
	
	// HitGage가 Max보다 높다면 Hit 애니메이션 재생
	if(_hitGageCurrentValue >=_hitGageMaxValue)
	{
		PlayAction(FGameplayTag::RequestGameplayTag("Action.Common.Hit"));
		GetPLStatisticComponent()->ModifyStat(STAT_HitGage, -_hitGageCurrentValue, false);
	}
	
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


int APLCharacter::GetRandomInt(int _min, int _max)
{
	std::random_device _rd;
	std::uniform_int_distribution<int> _dist(_min, _max);

	return _dist(_rd);
}

float APLCharacter::GetCurrentStatPercent(FGameplayTag _currentStat) const
{
	return  GetPLStatisticComponent()->GetCurrentCharacterStat(_currentStat).Value / GetPLStatisticComponent()->GetCurrentCharacterStat(_currentStat).MaxValue;
}

UPLAnimationInstance* APLCharacter::GetPLAnimationInstance() const
{
	return Cast<UPLAnimationInstance>(GetMesh()->GetAnimInstance());
}


