// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLAICharacter.h"

APLAICharacter::APLAICharacter()
{
	
}

void APLAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(AiSkillTimerHandle, this, &APLAICharacter::UpdateSkill, 1.0f, true);
}

void APLAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}


void APLAICharacter::UpdateSkill()
{
	//스킬 쿨타임 계산
	CalculateSkillColdTime();

	
}

void APLAICharacter::CalculateSkillColdTime()
{
	for(auto& _skillInfo : SkillInfo)
	{
		_skillInfo.CurrentSkillColdTime += 1.0f;
	}
}
