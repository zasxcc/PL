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
	GetWorld()->GetTimerManager().SetTimer(StatRegenTimer, this, &UPLStatisticComponent::RegenStat, 0.25f, true);
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
	/*  PLType.h 에 정의
	 *  #define STAT_HP FGameplayTag::RequestGameplayTag("Stat.HP")
	 */
	
	if(CharacterStat.Contains(STAT_HP))
	{
		ModifyStat(STAT_HP, -_damage, true);
		if(CharacterStat[STAT_HP].Value <= 0.0f)
		{
			DeadEvent();
		}
	}
}

void UPLStatisticComponent::DeadEvent()
{
	//Dead Event
	
	
}

float UPLStatisticComponent::CalculateDamage(FDamageInfo _damageInfo,  UPLStatisticComponent* _dealerStaticComp)
{
	/*  PLType.h 에 정의
	 *  #define STAT_ATK FGameplayTag::RequestGameplayTag("Stat.ATK")
	 *  #define STAT_DEF FGameplayTag::RequestGameplayTag("Stat.DEF")
	 */
	
	if(CharacterStat.Contains(STAT_DEF) &&
		_dealerStaticComp->CharacterStat.Contains(STAT_ATK))
	{
		return 100/(100+CharacterStat[STAT_DEF].Value)*(_damageInfo.Damage + _dealerStaticComp->CharacterStat[STAT_ATK].Value * _damageInfo.ATK_Ratio);
	}
	return 0.0f;
}


void UPLStatisticComponent::ModifyStat(FGameplayTag _modifyStat, float _addValue, bool _applyRegenDelay)
{
	if(CharacterStat.Contains(_modifyStat))
	{
		CharacterStat[_modifyStat].Value += _addValue;
		
		if(_applyRegenDelay)
		{
			CharacterStat[_modifyStat].CurrentRegenDelay = 0.0f;
		}
		
		//수정한 값이 최댓값보다 크다면 최댓값으로 (-1은 최댓값의 한계가 없는 스텟)
		if(CharacterStat[_modifyStat].Value >= CharacterStat[_modifyStat].MaxValue &&
			CharacterStat[_modifyStat].MaxValue  != -1)
		{
			CharacterStat[_modifyStat].Value = CharacterStat[_modifyStat].MaxValue;
		}
	}
}

void UPLStatisticComponent::InitStat()
{
	CharacterStat = DefaultCharacterStat;
}

void UPLStatisticComponent::RegenStat()
{
	for(auto& characterStat : CharacterStat)
	{
		//리젠되는 스텟이라면
		if(characterStat.Value.RegenValue)
		{
			//리젠 딜레이 검사
			if(characterStat.Value.CurrentRegenDelay >= characterStat.Value.RegenDelay)
			{
				//최댓값을 넘지 않도록
				if(characterStat.Value.Value < characterStat.Value.MaxValue)
				{
					//초당 리젠 값이 입력되어 있는데, 리젠은 0.25초마다 되므로 0.25 곱해야함
					characterStat.Value.Value += characterStat.Value.RegenValue * 0.25f;

					//마지막 한반의 리젠에서 최댓값을 넘는다면, 최댓값으로 
					if(characterStat.Value.Value > characterStat.Value.MaxValue)
					{
						characterStat.Value.Value = characterStat.Value.MaxValue;
					}
				}
			}
			//리젠 딜레이에 걸려있다면 리젠딜레이 수치 증가
			else
			{
				characterStat.Value.CurrentRegenDelay += 0.25f;
			}
		}
	}
}

