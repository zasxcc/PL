// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/PLAttackAction.h"
#include "Character/PLAICharacter.h"
#include "Character/PLPlayerCharacter.h"

void UPLAttackAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();
	const APLAICharacter* _aiCharacter = Cast<APLAICharacter>(OwnerCharacter);
	APLPlayerCharacter* _playerCharacter = Cast<APLPlayerCharacter>(OwnerCharacter);
	// AI 캐릭터일 경우
	if(IsValid(_aiCharacter) && IsValid(_aiCharacter->GetController()))
	{
		_aiCharacter->GetController()->StopMovement();
	}

	// Player 캐릭터일 경우
	else if(IsValid(_playerCharacter))
	{
		// 가드 불가로 변경
		_playerCharacter->GetPLPlayerController()->SetEnableGuard(false);
	}
}

void UPLAttackAction::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	
	APLPlayerCharacter* _playerCharacter = Cast<APLPlayerCharacter>(OwnerCharacter);

	if(_playerCharacter)
	{
		// 가드 가능으로 변경
		_playerCharacter->GetPLPlayerController()->SetEnableGuard(true);
	}
}

void UPLAttackAction::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}
