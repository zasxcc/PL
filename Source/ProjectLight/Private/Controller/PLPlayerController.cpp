// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PLPlayerController.h"

#include "Animation/PLAnimationInstance.h"
#include "Character//PLPlayerCharacter.h"
#include "Components/PLTargetingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

void APLPlayerController::TurnInPlace()
{
	// 타겟팅한 적이 있거나 속도가 1보다 클때
	if(IsValid(GetPLPlayerCharacter()->GetTargetingComponent()->CurrentTarget) || GetPLPlayerCharacter()->GetPLAnimationInstance()->GetCharacterSpeed() > 1.0f)
	{
		GetPLPlayerCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetPLPlayerCharacter()->GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
		TurnLeft = false;
		TurnRight = false;
	}
	// 움직이지 않고 타겟팅한 적이 없을 경우
	else
	{
		const FRotator _deltaRot = UKismetMathLibrary::NormalizedDeltaRotator(GetPLPlayerCharacter()->GetControlRotation(), GetPLPlayerCharacter()->GetActorRotation());
		if(_deltaRot.Yaw > 75.0f)
		{
			TurnRight = true;
			GetPLPlayerCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetPLPlayerCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
			GetPLPlayerCharacter()->GetCharacterMovement()->RotationRate = FRotator(0.0f, 120.0f, 0.0f);
		}
		else if(_deltaRot.Yaw < -75.0f)
		{
			TurnLeft = true;
			GetPLPlayerCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetPLPlayerCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
			GetPLPlayerCharacter()->GetCharacterMovement()->RotationRate = FRotator(0.0f, 120.0f, 0.0f);
		}
		else if(UKismetMathLibrary::NearlyEqual_FloatFloat(_deltaRot.Yaw,0.0f, 10.0f))
		{
			TurnLeft = false;
			TurnRight = false;
			GetPLPlayerCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetPLPlayerCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
		}
	}
}


void APLPlayerController::AssignTeam(ETeam _team)
{
	CharacterTeam = _team;
	SetGenericTeamId(static_cast<uint8>(CharacterTeam));
}

APLPlayerCharacter* APLPlayerController::GetPLPlayerCharacter()
{
	if(IsValid(PlayerCharacter) == false)
	{
		PlayerCharacter = Cast<APLPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		return PlayerCharacter;
	}
	return PlayerCharacter;
}