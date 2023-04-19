// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLCharacter.h"
#include "Components//PLStatisticComponent.h"
#include "GameplayTagContainer.h"
#include "Animation/PLAnimationInstance.h"
#include "Components/PLCollisionTraceComponent.h"
#include <random>
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
		
		ActionManagerComponent->ExecuteAction(ActionInfo[_actionTag].PlayAction);
		PlayAnimMontage(ActionInfo[_actionTag].PlayMontage);
	}
}

float APLCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 대미지 
	GetPLStatisticComponent()->ApplyDamage(DamageAmount);
	// HitGage 증가
	GetPLStatisticComponent()->ModifyStat(STAT_HitGage, DamageAmount, false);
	
	
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

float APLCharacter::GetAngleToTarget() const
{
	if (!GetCurrentTargetCharacter())
	{
		return 0.0f;
	}

	FVector Direction = GetCurrentTargetCharacter()->GetActorLocation() - GetActorLocation();
	Direction.Normalize();

	// Compute the angle between the two vectors
	const float DotProduct = FVector::DotProduct(GetActorForwardVector(), Direction);

	// Convert the angle from radians to degrees
	const float AngleInDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

	return AngleInDegrees;
}


int APLCharacter::GetRandomInt(int _min, int _max)
{
	std::random_device _rd;
	std::uniform_int_distribution<int> _dist(_min, _max);

	return _dist(_rd);
}

UPLAnimationInstance* APLCharacter::GetPLAnimationInstance() const
{
	return Cast<UPLAnimationInstance>(GetMesh()->GetAnimInstance());
}


