// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "PLCharacter.generated.h"


USTRUCT(BlueprintType)
struct FPlayActionInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL)
	class UAnimMontage* PlayMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = PL)
	class UPLActionBase* PlayAction = nullptr;
};

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
