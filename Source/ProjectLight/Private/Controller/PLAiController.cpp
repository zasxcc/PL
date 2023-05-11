// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PLAiController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PLAICharacter.h"
#include "Components/PLTeamManagerComponent.h"
#include "Controller/PLPlayerController.h"
#include "Game/ProjectLightGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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
	AiPerceptionComp->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
	
}

void APLAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerCharacter = Cast<APLAICharacter>(InPawn);
	if( !OwnerCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Error :: PLAIController :: OnPossess :: OwnerCharacter Is Not Valid"));
		return;
	}
	CharacterMovementComp = OwnerCharacter->FindComponentByClass<UCharacterMovementComponent>();
}

void APLAiController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	Super::UpdateControlRotation(DeltaTime, bUpdatePawn);
	// Smooth 턴
	if (bUpdatePawn)
	{
		const FRotator CurrentPawnRotation = OwnerCharacter->GetActorRotation();

		SmoothTargetRotation = UKismetMathLibrary::RInterpTo_Constant(OwnerCharacter->GetActorRotation(), ControlRotation, DeltaTime, SmoothFocusInterpSpeed);

		if (CurrentPawnRotation.Equals(SmoothTargetRotation, 1e-3f) == false)
		{
			// 타겟에게 부드럽게 회전
			OwnerCharacter->FaceRotation(SmoothTargetRotation, DeltaTime);
		}
	}
}

// 팀 별 관계 설정
ETeamAttitude::Type APLAiController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// Other 엑터가 PLCharacter 일 경우
	if(const APLCharacter* _otherPlCharacter = Cast<APLCharacter>(&Other))
	{
		const UPLTeamManagerComponent* _teamManagerComp = Cast<AProjectLightGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->TeamManagerComponent;
		const APLAiController* _otherPlCharacterController = Cast<APLAiController>(_otherPlCharacter->GetController());
		const APLPlayerController* _playerController = Cast<APLPlayerController>(_otherPlCharacter->GetController());

		// Other가 AiCharacter일 경우
		if(IsValid(_teamManagerComp) && IsValid(_otherPlCharacterController))
		{
			if(_teamManagerComp->IsEnemyTeam(CharacterTeam, _otherPlCharacterController->CharacterTeam))
			{
				return ETeamAttitude::Hostile;
			}
			return ETeamAttitude::Friendly;
			
		}
		// Other가 플레이어 캐릭터일 경우
		if(IsValid(_teamManagerComp) && IsValid(_playerController))
		{
			if(_teamManagerComp->IsEnemyTeam(CharacterTeam, _playerController->CharacterTeam))
			{
				return ETeamAttitude::Hostile;
			}
			return ETeamAttitude::Friendly;
		}

		return ETeamAttitude::Friendly;
		
	}

	// Other 엑터가 PLCharacter가 아니고 Pawn 일 경우,
	else if ( const APawn* OtherPawn = Cast<APawn>(&Other))
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
				return ETeamAttitude::Hostile;
			}
			if (OtherTeamAgent->GetGenericTeamId() == GetGenericTeamId()) 
			{
				return ETeamAttitude::Friendly;
			}
			else if(OtherTeamAgent->GetGenericTeamId() == static_cast<uint8>(ETeam::ENeutral))
			{
				return ETeamAttitude::Neutral;
			}

			return ETeamAttitude::Hostile;
		}
	}
	return ETeamAttitude::Neutral;
}


void APLAiController::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	Super::GetActorEyesViewPoint(OutLocation, OutRotation);
	if(OwnerCharacter)
	{
		FTransform tr = OwnerCharacter->GetActorTransform();
		OutLocation = tr.GetLocation();
		OutRotation = tr.Rotator();
	}
}

//////////////////////////// 팀 관련 함수 /////////////////////
void APLAiController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	//IGenericTeamAgentInterface::SetGenericTeamId(InTeamID);
	CharacterTeam = static_cast<ETeam>(InTeamID.GetId());
}



FGenericTeamId APLAiController::GetGenericTeamId() const
{
	return static_cast<uint8>(CharacterTeam);
}

// 팀 등록
void APLAiController::AssignTeam(ETeam _team)
{
	CharacterTeam = _team;
	SetGenericTeamId(static_cast<uint8>(CharacterTeam));
}
///////////////////////////////////////////////////////////////

// Ai perception Update 
void APLAiController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	APLCharacter* _plCharacter = Cast<APLCharacter>(Actor);
	
	if(IsValid(_plCharacter))
	{
		if(Stimulus.WasSuccessfullySensed() == true)
		{
			switch (Stimulus.Type)
			{
			case 0:
				// react to sight stimulus
				Blackboard->SetValueAsObject("CurrentTargetActor",Actor);
				CharacterMovementComp->bOrientRotationToMovement = false;
				CharacterMovementComp->bUseControllerDesiredRotation = true;
				OwnerCharacter->SetCurrentTargetCharacter(_plCharacter);
				SetFocus(OwnerCharacter->GetCurrentTargetCharacter());
				StopMovement();
				break;
			case 1:
				// react to hearing stimulus
			
				break;
		
			default:
			
				break;
			}
		}
		else if(Stimulus.WasSuccessfullySensed() == false)
		{
			switch (Stimulus.Type)
			{
			case 0:
				// react to sight stimulus
				//Blackboard->ClearValue("CurrentTargetActor");
				//CharacterMovementComp->bOrientRotationToMovement = true;
				//CharacterMovementComp->bUseControllerDesiredRotation = false;
				//SetFocus(nullptr);
				break;
			case 1:
				// react to hearing stimulus
			
				break;
		
			default:
			
				break;
			}
		}
	}
}
