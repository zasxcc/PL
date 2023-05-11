// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PLCharacter.h"
#include "Components/ActorComponent.h"
#include "PLActionManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIGHT_API UPLActionManagerComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UPLActionManagerComponent();

	UPROPERTY(BlueprintReadWrite, Category=PL)
	class UPLActionBase* CurrentAction;

private:
	UPROPERTY()
	class APLCharacter* OwnerCharacter;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category=PL)
	bool ExecuteAction(class UPLActionBase* _executeAction);

	UFUNCTION(BlueprintCallable, Category=PL)
	void ExitAction();

	UFUNCTION(BlueprintPure, Category=PL)
	class APLCharacter* GetPLOwnerCharacter();

	UFUNCTION()
	void HandleMontageFinished(UAnimMontage* _animMontage, bool _bInterruptted);

	UFUNCTION()
	void HandleMontageStarted(UAnimMontage* _animMontage);

	UFUNCTION()
	void HandleMontageBlendingOut(UAnimMontage* _animMontage, bool _bInterruptted);

		
};

