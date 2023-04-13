// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PLType.h"
#include "Components/ActorComponent.h"
#include "PLTeamManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIGHT_API UPLTeamManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPLTeamManagerComponent();

	TArray<TEnumAsByte<ECollisionChannel>> GetAllCollisionChannels(bool bIgnoreNeutral) const;
	TArray<TEnumAsByte<ECollisionChannel>> GetEnemyCollisionChannels(ETeam SelfTeam) const;

	UFUNCTION(BlueprintPure, Category = ACF)
	TEnumAsByte<ECollisionChannel> GetCollisionChannelByTeam(ETeam Team) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TMap<ETeam, FTeamInfo> Teams;

	UFUNCTION(BlueprintPure, Category = ACF)
	bool IsEnemyTeam(ETeam SelfTeam, ETeam TargetTeam) const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};


