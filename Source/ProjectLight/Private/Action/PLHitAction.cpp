// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/PLHitAction.h"

#include "Character/PLAICharacter.h"
#include "Character/PLPlayerCharacter.h"

void UPLHitAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();
	
	APLAICharacter* _aiCharacter = Cast<APLAICharacter>(OwnerCharacter);
	APLPlayerCharacter* _playerCharacter = Cast<APLPlayerCharacter>(OwnerCharacter);
	// AI 캐릭터일 경우
	if(IsValid(_aiCharacter) && IsValid(_aiCharacter->GetController()))
	{
		// 이동 스탑
		_aiCharacter->GetController()->StopMovement();

		// 현재 타겟팅한 적이 없다면
		if(!IsValid(_aiCharacter->GetCurrentTargetCharacter()))
		{
			// DamageCauser가 Null이 아니라면
			if(Cast<APLCharacter>(_aiCharacter->GetLastDamageInfo().DamageCauser))
			{
				// DamageCauser를 CurrentTarget으로 설정
				_aiCharacter->SetCurrentTargetCharacter(Cast<APLCharacter>(_aiCharacter->GetLastDamageInfo().DamageCauser));
			}
		}
	}

	// Player 캐릭터일 경우
	else if(IsValid(_playerCharacter))
	{
		// 공격, 회피, 가드 불가로 변경
		_playerCharacter->GetPLPlayerController()->SetEnableAttack(false);
		_playerCharacter->GetPLPlayerController()->SetEnableDodge(false);
		_playerCharacter->GetPLPlayerController()->SetEnableGuard(false);
	}
}

void UPLHitAction::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

	APLPlayerCharacter* _playerCharacter = Cast<APLPlayerCharacter>(OwnerCharacter);\
	if(_playerCharacter)
	{
		// 공격, 회피, 가드 가능으로 변경
		_playerCharacter->GetPLPlayerController()->SetEnableAttack(true);
		_playerCharacter->GetPLPlayerController()->SetEnableDodge(true);
		_playerCharacter->GetPLPlayerController()->SetEnableGuard(true);
	}
}

void UPLHitAction::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}
