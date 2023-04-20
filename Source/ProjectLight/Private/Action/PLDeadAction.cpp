// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/PLDeadAction.h"

#include "Character/PLAICharacter.h"

void UPLDeadAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();
	const APLAICharacter* _aiCharacter = Cast<APLAICharacter>(OwnerCharacter);
	// AI 캐릭터일 경우
	if(IsValid(_aiCharacter) && IsValid(_aiCharacter->GetController()))
	{
		_aiCharacter->GetController()->StopMovement();
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
