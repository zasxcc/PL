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

	// 현재 CurrentAction이 nullptr이 아니라면, Tick 함수 실행
	if(IsValid(CurrentAction))
	{
		CurrentAction->OnTick(DeltaTime);
	}
	// ...
}

bool UPLActionManagerComponent::ExecuteAction(UPLActionBase* _executeAction)
{
	/*기존에 CurrentAction이 이미 있다면, ExitAction 함수 실행*/
	if(CurrentAction)
	{
		ExitAction();
	}
	CurrentAction = _executeAction;
	if(CurrentAction)
	{
		// 액션 실행 조건에 맞지 않으면 리턴
		if(CurrentAction->CanExecuteAction(OwnerCharacter) == false)
		{
			return false;
		}
		
		CurrentAction->OwnerCharacter = OwnerCharacter;
		CurrentAction->OnActionStarted();
	}
	UPLAnimationInstance* _animInstance = Cast<UPLAnimationInstance>(GetPLOwnerCharacter()->GetPLAnimationInstance());

	if(GetPLOwnerCharacter()->GetPLAnimationInstance())
	{
		// 몽타주 Delegate 초기화
		GetPLOwnerCharacter()->GetPLAnimationInstance()->OnMontageStarted.Clear();
		GetPLOwnerCharacter()->GetPLAnimationInstance()->OnMontageBlendingOut.Clear();
		GetPLOwnerCharacter()->GetPLAnimationInstance()->OnMontageEnded.Clear();

		// 몽타주 Delegate 재세팅
		_animInstance->OnMontageStarted.AddDynamic(this, &UPLActionManagerComponent::HandleMontageStarted);
		_animInstance->OnMontageEnded.AddDynamic(this, &UPLActionManagerComponent::HandleMontageFinished);
		_animInstance->OnMontageBlendingOut.AddDynamic(this, &UPLActionManagerComponent::HandleMontageBlendingOut);

		return true;
	}
	return false;
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

	// 정상적 종료라면 ExitAction() 실행
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