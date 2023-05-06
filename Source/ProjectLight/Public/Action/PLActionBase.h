// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PLCharacter.h"
#include "UObject/NoExportTypes.h"
#include "PLActionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class PROJECTLIGHT_API UPLActionBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category=PL)
	TObjectPtr<APLCharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadWrite, Category=PL)
	TObjectPtr<UAnimMontage> PlayMontage;


public:
	/*엑션이 성공적으로 실행 될 때 트리거*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	void OnActionStarted();
	virtual void OnActionStarted_Implementation();

	/*액션이 끝나면 트리거.*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	void OnActionEnded();
	virtual void OnActionEnded_Implementation();

	/*액션 Tick*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	void OnTick(float DeltaTime);
	virtual void OnTick_Implementation(float DeltaTime);

	/*몽타주의 섹션이름을 찾아서 그 섹션 재생*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	FName GetMontageSectionName();
	virtual FName GetMontageSectionName_Implementation();

	/*실행 조건 검사*/
	UFUNCTION(BlueprintNativeEvent, Category = PL)
	bool CanExecuteAction(class APLCharacter* owner);
	virtual bool CanExecuteAction_Implementation(class APLCharacter* owner);
};
