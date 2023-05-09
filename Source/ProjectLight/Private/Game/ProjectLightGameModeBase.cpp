// Copyright Epic Games, Inc. All Rights Reserved.


#include "Game/ProjectLightGameModeBase.h"

#include "Components/PLTeamManagerComponent.h"

AProjectLightGameModeBase::AProjectLightGameModeBase()
{
	TeamManagerComponent = CreateDefaultSubobject<UPLTeamManagerComponent>(TEXT("TeamManagerComp"));
}
