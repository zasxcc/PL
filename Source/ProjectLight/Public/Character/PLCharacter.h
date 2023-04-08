// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Game/PLType.h"
#include "PLCharacter.generated.h"




UCLASS()
class PROJECTLIGHT_API APLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APLCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PL)
	TMap<FGameplayTag, FPlayActionInfo> ActionInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	class UPLStatisticComponent* StatisticComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	class UPLActionManagerComponent* ActionManagerComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category=PL)
	void PlayAction(FGameplayTag _actionTag);

	
	/*Getter, Setter*/
	UFUNCTION(BlueprintPure, Category=PL)
	class UPLStatisticComponent* GetPLStatisticComponent() const
	{
		return StatisticComponent;
	}

	UFUNCTION(BlueprintPure, Category=PL)
	class UPLActionManagerComponent* GetPLActionComponent() const
	{
		return ActionManagerComponent;
	}

	UFUNCTION(BlueprintPure, Category=PL)
	class UPLAnimationInstance* GetPLAnimationInstance() const;
	/////////////////
	
};
