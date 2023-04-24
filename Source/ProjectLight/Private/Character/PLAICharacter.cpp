// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLAICharacter.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Perception/AIPerceptionComponent.h"

APLAICharacter::APLAICharacter()
{
	AiPerceptionStimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AiperceptionStimuliSource"));
}

void APLAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// 스킬 업데이트 타이머 
	GetWorld()->GetTimerManager().SetTimer(AiSkillTimerHandle, this, &APLAICharacter::UpdateSkill, 0.1f, true);
}

void APLAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void APLAICharacter::UpdateSkill()
{
	//스킬 쿨타임 계산
	CalculateSkillColdTime();
	
	//전투 상태일 때만, 스킬 사용 여부 검사 및 스킬 사용
	if(CharacterState == ECharacterState::ECombat)
	{
		if(IsValid(CurrentTargetCharacter))
		{
			// 랜덤으로 스킬 인덱스 찝어서 검사
			const int _randomSkillIndex = GetRandomInt(0, SkillInfo.Num()-1);

			if(SkillInfo.IsValidIndex(_randomSkillIndex))
			{
				if(SkillInfo[_randomSkillIndex].ActivateSkillDistance >= GetDistanceFromCurrentTarget() &&				// 스킬 사용가능한 타겟과의 거리 검사
					SkillInfo[_randomSkillIndex].SkillColdTime <= SkillInfo[_randomSkillIndex].CurrentSkillColdTime &&  // 스킬 쿨타임 검사
					SkillInfo[_randomSkillIndex].ActivateSKillAngle >= GetAngleToTarget() &&							// 스킬 사용가능한 타겟과의 각도 검사
					ActionInfo.Contains(FGameplayTag::RequestGameplayTag("Action.Ai.RandomSkill")))					// 스킬 사용에 필요한 값을 ActionInfo가 가지고 있는지	검사		
				{
					// 스킬 사용을 위해 ActionInfo[Action.Ai.RandomSkill] 값 설정 
					ActionInfo[FGameplayTag::RequestGameplayTag("Action.Ai.RandomSkill")] = SkillInfo[_randomSkillIndex].PlayMontageAndAction;
					// 스킬 사용
					PlayAction(FGameplayTag::RequestGameplayTag("Action.Ai.RandomSkill"));
					// 사용한 스킬 쿨타임 초기화
					SkillInfo[_randomSkillIndex].CurrentSkillColdTime = 0.0f;
				}
			}
		}
	}
}

void APLAICharacter::CalculateSkillColdTime()
{
	for(auto& _skillInfo : SkillInfo)
	{
		_skillInfo.CurrentSkillColdTime += 0.1f;
	}
}

float APLAICharacter::GetDistanceFromCurrentTarget() const
{
	if(IsValid(CurrentTargetCharacter))
	{
		return GetDistanceTo(CurrentTargetCharacter);
	}
	return -1.0f;
}
