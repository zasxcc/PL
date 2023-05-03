// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/PLActionBase.h"

void UPLActionBase::OnActionStarted_Implementation()
{
	
}

void UPLActionBase::OnActionEnded_Implementation()
{
	
}

void UPLActionBase::OnTick_Implementation(float DeltaTime)
{
}

FName UPLActionBase::GetMontageSectionName_Implementation()
{
	const FName _sectionName;
	return _sectionName;
}

bool UPLActionBase::CanExecuteAction_Implementation(APLCharacter* owner)
{
	return true;
}
