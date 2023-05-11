// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLBossCharacter.h"
#include "Components/PointLightComponent.h"

APLBossCharacter::APLBossCharacter()
{
	FlickeringPointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("FlickerPointLightComp"));
	FlickeringPointLightComponent->SetupAttachment(GetMesh(), "FlickerSock");
}

void APLBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APLBossCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APLBossCharacter::DeadEvent()
{
	Super::DeadEvent();
}

void APLBossCharacter::BecomeTargetEvent()
{
	//Super::BecomeTargetEvent();
}

void APLBossCharacter::BecomeNonTargetEvent()
{
	//Super::BecomeNonTargetEvent();
}

void APLBossCharacter::SetFlickeringLight_Flicker(float _time, float _flickerInterval, FName _attachSockName, FTransform _attachOffset)
{
	// 이미 타이머가 진행중이면 클리어
	if(FlickerIntervalTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FlickerIntervalTimer);
	}

	// 플리커 라이트 어테치
	FlickeringPointLightComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, _attachSockName);
	FlickeringPointLightComponent->SetRelativeTransform(_attachOffset);

	// 포인트 라이트 깜빡임 타이머 셋
	GetWorld()->GetTimerManager().SetTimer(FlickerIntervalTimer, this, &APLBossCharacter::LightFlicker, _flickerInterval, true);

	// 포인트 라이트 깜빡임 지속시간 타이머 셋
	GetWorld()->GetTimerManager().SetTimer(FlickerTimer, FTimerDelegate::CreateLambda([&]()
	{
		if(FlickerIntervalTimer.IsValid())
		{
			GetWorldTimerManager().ClearTimer(FlickerIntervalTimer);
		}
	}), _time, false); 
	
}

void APLBossCharacter::StopFlickeringPointLight(bool _lightOn)
{
	if(FlickerIntervalTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FlickerIntervalTimer);
	}
	if(FlickerTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FlickerTimer);
	}

	if(_lightOn)
	{
		GetFlickerPointLight()->SetLightingChannels(false, true, false);
		HasFlickerLightChannel2 = true;
	}
	else if(_lightOn == false)
	{
		GetFlickerPointLight()->SetLightingChannels(false, false, false);
		HasFlickerLightChannel2 = false;
	}

}

void APLBossCharacter::LightFlicker()
{
	if(HasFlickerLightChannel2)
	{
		GetFlickerPointLight()->SetLightingChannels(false, false, false);
		HasFlickerLightChannel2 = false;
	}
	else
	{
		GetFlickerPointLight()->SetLightingChannels(false, true, false);
		HasFlickerLightChannel2 = true;
	}
}
