// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PLAICharacter.h"
#include "PLBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API APLBossCharacter : public APLAICharacter
{
	GENERATED_BODY()

public:
	APLBossCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void DeadEvent() override;
	virtual void BecomeTargetEvent() override;
	virtual void BecomeNonTargetEvent() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PL_Character)
	TObjectPtr<class UPointLightComponent> FlickeringPointLightComponent;

private:
	UPROPERTY()
	FTimerHandle FlickerTimer;

	UPROPERTY()
	FTimerHandle FlickerIntervalTimer;

	bool HasFlickerLightChannel2 = true;
	
	
public:
	// 포인트 라이트 깜빡임 셋
	UFUNCTION(BlueprintCallable)
	void SetFlickeringLight_Flicker(float _time, float _flickerInterval, FName _attachSockName, FTransform _attachOffset);

	// 포인트 라이트 깜빡임 정지
	UFUNCTION(BlueprintCallable)
	void StopFlickeringPointLight(bool _lightOn);

	// 함수 호출 시, HasFlickerLightChannel2에 따라 FlickerPointLightComponent이 켜지거나 꺼지거나 
	UFUNCTION()
	void LightFlicker();

	//////////Getter, Setter////////////
	UFUNCTION(BlueprintPure)
	class UPointLightComponent* GetFlickerPointLight() const
	{
		return FlickeringPointLightComponent;
	}
};
