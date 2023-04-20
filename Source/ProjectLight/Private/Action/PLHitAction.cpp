// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/PLHitAction.h"

#include "Character/PLAICharacter.h"

void UPLHitAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();
	
	APLAICharacter* _aiCharacter = Cast<APLAICharacter>(OwnerCharacter);
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
}

void UPLHitAction::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UPLHitAction::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}
