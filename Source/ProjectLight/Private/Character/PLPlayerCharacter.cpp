// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/PLTargetingComponent.h"
#include "GameFramework/SpringArmComponent.h"

APLPlayerCharacter::APLPlayerCharacter()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponenet"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	TargetingComp = CreateDefaultSubobject<UPLTargetingComponent>(TEXT("TargetingComponent"));

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
}

void APLPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APLPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APLPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APLPlayerCharacter::TriggerSkill(FGameplayTag _triggerSkillTag)
{
	if(ActionInfo.Contains(_triggerSkillTag))
	{
		PlayAction(_triggerSkillTag);
	}
}
