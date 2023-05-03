// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/PLDeadAction.h"

#include "Character/PLAICharacter.h"
#include "Character/PLPlayerCharacter.h"
#include "Controller/PLAiController.h"
#include "Controller/PLPlayerController.h"

void UPLDeadAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();
	const APLAICharacter* _aiCharacter = Cast<APLAICharacter>(OwnerCharacter);
	APLPlayerCharacter* _playerCharacter = Cast<APLPlayerCharacter>(OwnerCharacter);
	// AI 캐릭터일 경우
	if(IsValid(_aiCharacter) && IsValid(_aiCharacter->GetPLAiController()))
	{
		_aiCharacter->GetPLAiController()->StopMovement();
		_aiCharacter->GetPLAiController()->SetFocus(nullptr);
	}

	// Player 캐릭터 일 경우
	else if(IsValid(_playerCharacter))
	{
		// 공격, 회피, 가드 불가로 변경
		_playerCharacter->GetPLPlayerController()->SetEnableAttack(false);
		_playerCharacter->GetPLPlayerController()->SetEnableDodge(false);
		_playerCharacter->GetPLPlayerController()->SetEnableGuard(false);
	}
}

void UPLDeadAction::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UPLDeadAction::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}
