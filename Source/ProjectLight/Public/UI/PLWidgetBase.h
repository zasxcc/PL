// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PLWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHT_API UPLWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PL_Widget, meta=(ExposeOnSpawn =true))
	TObjectPtr<class APLCharacter> OwnerPLCharacter; 
	
};
