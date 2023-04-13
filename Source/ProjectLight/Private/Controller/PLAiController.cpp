// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PLAiController.h"

#include "Perception/AIPerceptionComponent.h"

APLAiController::APLAiController()
{
	AiPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AiperceptionComp"));
}

void APLAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APLAiController::BeginPlay()
{
	Super::BeginPlay();
}
