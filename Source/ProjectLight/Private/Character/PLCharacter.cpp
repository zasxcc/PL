// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLCharacter.h"
#include "Components//PLStatisticComponent.h"
#include "GameplayTagContainer.h"
#include "Animation/PLAnimationInstance.h"
#include "Components/PLCollisionTraceComponent.h"
#include "Components/PLActionManagerComponent.h"

// Sets default values
APLCharacter::APLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatisticComponent = CreateDefaultSubobject<UPLStatisticComponent>(TEXT("Stat Comp"));
	ActionManagerComponent = CreateDefaultSubobject<UPLActionManagerComponent>(TEXT("Action Comp"));
	CollisionTraceComponent = CreateDefaultSubobject<UPLCollisionTraceComponent>(TEXT("Collision Comp"));
	
}

// Called when the game starts or when spawned
void APLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APLCharacter::PlayAction(FGameplayTag _actionTag)
{
	if(ActionInfo.Contains(_actionTag))
	{
		// StoredActionInfo에 재생할 Action과 Montage 저장 
		ActionManagerComponent->StoredActionInfo = ActionInfo[_actionTag];
		
		ActionManagerComponent->ExecuteAction(ActionInfo[_actionTag].PlayAction);
		PlayAnimMontage(ActionInfo[_actionTag].PlayMontage);
	}
}

UPLAnimationInstance* APLCharacter::GetPLAnimationInstance() const
{
	return Cast<UPLAnimationInstance>(GetMesh()->GetAnimInstance());
}


