// Fill out your copyright notice in the Description page of Project Settings.


#include "Components//PLStatisticComponent.h"

// Sets default values for this component's properties
UPLStatisticComponent::UPLStatisticComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPLStatisticComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetTimerManager().SetTimer(StatRegenTimer, this, &UPLStatisticComponent::RegenStat, 0.2f, true);
	CharacterStat = DefaultCharacterStat; 
}


// Called every frame
void UPLStatisticComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPLStatisticComponent::ApplyDamage(float _damage)
{
	CharacterStat.HP.Value -= _damage;
	if(CharacterStat.HP.Value <= 0.0f)
	{
		DeadEvent();
	}
}

void UPLStatisticComponent::DeadEvent()
{
	//Dead Event
	
}

float UPLStatisticComponent::CalculateDamage(FDamageInfo _damageInfo,  UPLStatisticComponent* _dealerStaticComp)
{
	return 100/(100+CharacterStat.DEF.Value)*(_damageInfo.Damage + _dealerStaticComp->CharacterStat.ATK.Value * _damageInfo.ATK_Ratio);
}

void UPLStatisticComponent::InitStat()
{
	CharacterStat = DefaultCharacterStat;
}

void UPLStatisticComponent::RegenStat()
{
	
}

