// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PLAiController.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

APLAiController::APLAiController()
{
	AiPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AiperceptionComp"));
}

void APLAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APLAiController::BeginPlay()
{
	Super::BeginPlay();
	AssignTeam(CharacterTeam);
	AiPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated_Delegate);
}

ETeamAttitude::Type APLAiController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (APawn const* OtherPawn = Cast<APawn>(&Other))
	{
		if (auto const OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			if(GetGenericTeamId() == static_cast<uint8>(ETeam::ETeam4_Alliance))
			{
				if (OtherTeamAgent->GetGenericTeamId() == GetGenericTeamId() || OtherTeamAgent->GetGenericTeamId() == static_cast<uint8>(ETeam::ETeam1_Player)) 
				{
					return ETeamAttitude::Friendly;
				}
				else if(OtherTeamAgent->GetGenericTeamId() == static_cast<uint8>(ETeam::ENeutral))
				{
					return ETeamAttitude::Neutral;
				}
				else 
				{
					return ETeamAttitude::Hostile;
				}
			}
			if (OtherTeamAgent->GetGenericTeamId() == GetGenericTeamId()) 
			{
				return ETeamAttitude::Friendly;
			}
			else if(OtherTeamAgent->GetGenericTeamId() == static_cast<uint8>(ETeam::ENeutral))
			{
				return ETeamAttitude::Neutral;
			}
			else 
			{
				return ETeamAttitude::Hostile;
			}
		}
	}
	return ETeamAttitude::Neutral;
}

void APLAiController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	//IGenericTeamAgentInterface::SetGenericTeamId(InTeamID);
	CharacterTeam = static_cast<ETeam>(InTeamID.GetId());
}

FGenericTeamId APLAiController::GetGenericTeamId() const
{
	return static_cast<uint8>(CharacterTeam);
}


void APLAiController::AssignTeam(ETeam _team)
{
	CharacterTeam = _team;
	SetGenericTeamId(static_cast<uint8>(CharacterTeam));
}


void APLAiController::OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus)
{
	switch (Stimulus.Type)
	{
	case 0:
		// react to sight stimulus
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Sight"));
		break;
	case 1:
		// react to hearing;
		
	default:
		return;
	}
}
