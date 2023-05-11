// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PLLightFlickerNotifyState.h"
#include "Character/PLBossCharacter.h"

void UPLLightFlickerNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	APLBossCharacter* _bossCharacter = Cast<APLBossCharacter>(MeshComp->GetOwner());
	if(IsValid(_bossCharacter))
	{
		_bossCharacter->SetFlickeringLight_Flicker(FlickerDurationTime, FlickerInterval, AttachSockName, AttachOffset);
	}
}

void UPLLightFlickerNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	APLBossCharacter* _bossCharacter = Cast<APLBossCharacter>(MeshComp->GetOwner());
	if(IsValid(_bossCharacter))
	{
		_bossCharacter->StopFlickeringPointLight(false);
	}
}
