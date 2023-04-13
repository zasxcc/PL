// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectLightGameModeBase.h"

#include "Components/PLTeamManagerComponent.h"

AProjectLightGameModeBase::AProjectLightGameModeBase()
{
	TeamManagerComponent = CreateDefaultSubobject<UPLTeamManagerComponent>(TEXT("TeamManagerComp"));
}
