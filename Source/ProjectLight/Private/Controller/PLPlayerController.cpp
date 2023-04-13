// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PLPlayerController.h"

APLPlayerController::APLPlayerController()
{
	
}

void APLPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AssignTeam(CharacterTeam);
}


void APLPlayerController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	//IGenericTeamAgentInterface::SetGenericTeamId(InTeamID);
	CharacterTeam = static_cast<ETeam>(InTeamID.GetId());
}

FGenericTeamId APLPlayerController::GetGenericTeamId() const
{
	return static_cast<uint8>(CharacterTeam);
}


void APLPlayerController::AssignTeam(ETeam _team)
{
	CharacterTeam = _team;
	SetGenericTeamId(static_cast<uint8>(CharacterTeam));
}