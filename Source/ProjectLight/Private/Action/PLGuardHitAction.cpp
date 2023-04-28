// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/PLGuardHitAction.h"

#include "Character/PLPlayerCharacter.h"

void UPLGuardHitAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();
	OwnerCharacter->SetIsGuard(false);
}

void UPLGuardHitAction::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	// APLPlayerCharacter* _playerCharacter = Cast<APLPlayerCharacter>(OwnerCharacter);
	// if(IsValid(_playerCharacter))
	// {
	// 	if(_playerCharacter->GetPLPlayerController()->IsInputKeyDown(EKeys::RightMouseButton))
	// 	{
	// 		_playerCharacter->StartGuard();
	// 	}
	// }
}
