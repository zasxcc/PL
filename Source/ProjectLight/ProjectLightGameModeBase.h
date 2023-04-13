// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectLightGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API AProjectLightGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_GameState)
	TObjectPtr<class UPLTeamManagerComponent> TeamManagerComponent;

	AProjectLightGameModeBase();
};
