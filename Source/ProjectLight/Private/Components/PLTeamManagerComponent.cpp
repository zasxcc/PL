// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PLTeamManagerComponent.h"

// Sets default values for this component's properties
UPLTeamManagerComponent::UPLTeamManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	for(uint8 i = 0; i < Teams.Num();i++)
	{
		FTeamInfo TeamInfo = FTeamInfo();

		ETeam CurrentTeam = static_cast<ETeam>(i);
		//TeamInfo.DisplayName = FText::FromString(FString::Printf(TEXT("Team %d"),(i+1)));


		for(uint8 j = 0; j < Teams.Num(); j++)
		{
			const ETeam TargetTeam = static_cast<ETeam>(j);
			ETeamAttitude::Type Attitude;

			if(CurrentTeam == ETeam::ENeutral)
			{
				Attitude = ETeamAttitude::Neutral;
			}else
			{
				if(CurrentTeam == TargetTeam)
				{
					Attitude = ETeamAttitude::Friendly;
				}
				else if(TargetTeam == ETeam::ENeutral)
				{
					Attitude = ETeamAttitude::Neutral;
				}else
				{
					Attitude = ETeamAttitude::Hostile;
				}
			}

			TeamInfo.Relationship.Add(TargetTeam, Attitude);
			
		}
		
		Teams.Add(CurrentTeam, TeamInfo);
	}
	// ...
}


// Called when the game starts
void UPLTeamManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPLTeamManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<TEnumAsByte<ECollisionChannel>> UPLTeamManagerComponent::GetAllCollisionChannels(bool bIgnoreNeutral) const
{
	TArray<TEnumAsByte<ECollisionChannel>> channels;
	
	for(int32 i = 0; i < Teams.Num();i++)
	{
		const ETeam TargetTeam = static_cast<ETeam>(i);
		if (TargetTeam == ETeam::ENeutral && bIgnoreNeutral) {
			continue;
		}		
		channels.Add(GetCollisionChannelByTeam(TargetTeam));
	}
	return channels;
}

TArray<TEnumAsByte<ECollisionChannel>> UPLTeamManagerComponent::GetEnemyCollisionChannels(ETeam SelfTeam) const
{
	TArray<TEnumAsByte<ECollisionChannel>> channels;
	
	for(uint8 i = 0; i < Teams.Num();i++)
	{
		const ETeam TargetTeam = static_cast<ETeam>(i);
		
		if(IsEnemyTeam(SelfTeam, TargetTeam))
		{
			channels.Add(GetCollisionChannelByTeam(TargetTeam));
		}
	}
	return channels;
}

TEnumAsByte<ECollisionChannel> UPLTeamManagerComponent::GetCollisionChannelByTeam(ETeam Team) const
{
	if (Teams.Contains(Team)) {
		return Teams.Find(Team)->CollisionChannel;
	}
	
	return ECollisionChannel::ECC_MAX;
}

bool UPLTeamManagerComponent::IsEnemyTeam(ETeam SelfTeam, ETeam TargetTeam) const
{
	if (Teams.Contains(SelfTeam))
	{
		const FTeamInfo* teamInfo = Teams.Find(SelfTeam);
		if (teamInfo && teamInfo->Relationship.Contains(TargetTeam))
		{
			return teamInfo->Relationship.Find(TargetTeam)->GetValue() == ETeamAttitude::Hostile;
		}
	}

	return false;
}