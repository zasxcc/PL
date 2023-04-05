// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PLActionManagerComponent.h"

#include "Action/PLActionBase.h"
#include "Animation/PLAnimationInstance.h"
#include "Character/PLCharacter.h"

// Sets default values for this component's properties
UPLActionManagerComponent::UPLActionManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPLActionManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<APLCharacter>(GetOwner());
	// ...
	
}


// Called every frame
void UPLActionManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CurrentAction)
	{
		CurrentAction->OnTick(DeltaTime);
	}
	// ...
}

void UPLActionManagerComponent::ExecuteAction(UPLActionBase* _executeAction)
{
	/*기존에 CurrentAction이 이미 있다면, ExitAction 함수 실행*/
	if(CurrentAction)
	{
		ExitAction();
	}
	CurrentAction = _executeAction;
	CurrentAction->OnActionStarted();
	
	UPLAnimationInstance* _animInstance = Cast<UPLAnimationInstance>(GetPLOwnerCharacter()->GetPLAnimationInstance());

	if(GetPLOwnerCharacter()->GetPLAnimationInstance())
	{
		GetPLOwnerCharacter()->GetPLAnimationInstance()->OnMontageStarted.Clear();
		GetPLOwnerCharacter()->GetPLAnimationInstance()->OnMontageBlendingOut.Clear();
		GetPLOwnerCharacter()->GetPLAnimationInstance()->OnMontageEnded.Clear();
		
		_animInstance->OnMontageStarted.AddDynamic(this, &UPLActionManagerComponent::HandleMontageStarted);
		_animInstance->OnMontageEnded.AddDynamic(this, &UPLActionManagerComponent::HandleMontageFinished);
		_animInstance->OnMontageBlendingOut.AddDynamic(this, &UPLActionManagerComponent::HandleMontageBlendingOut);
	}
}

void UPLActionManagerComponent::ExitAction()
{
	CurrentAction->OnActionEnded();
	CurrentAction = nullptr;

}

APLCharacter* UPLActionManagerComponent::GetPLOwnerCharacter()
{
	if(IsValid(OwnerCharacter) == false)
	{
		OwnerCharacter = Cast<APLCharacter>(GetOwner());
	}
	return OwnerCharacter;
}

void UPLActionManagerComponent::HandleMontageStarted(UAnimMontage* _animMontage)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("MG Start"));
	
}

void UPLActionManagerComponent::HandleMontageFinished(UAnimMontage* _animMontage, bool _bInterruptted)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("MG Finish"));
	if(_bInterruptted == false)
	{
		if(CurrentAction)
		{
			ExitAction();
		}
	}
}

void UPLActionManagerComponent::HandleMontageBlendingOut(UAnimMontage* _animMontage, bool _bInterruptted)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("MG BlendingOut"));
}