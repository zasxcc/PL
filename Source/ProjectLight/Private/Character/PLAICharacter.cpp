// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PLAICharacter.h"

#include "ActorOptimizeSubjectComponent.h"
#include "NiagaraComponent.h"
#include "Animation/PLAnimationInstance.h"
#include "Components/WidgetComponent.h"
#include "Controller/PLAiController.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "UI/PLWidgetBase.h"

APLAICharacter::APLAICharacter()
{
	AiPerceptionStimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AiperceptionStimuliSource"));
	FarDistanceEffect_01 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect01"));
	FarDistanceEffect_02 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect02"));
	EnemyUIWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	OptimizeSubjectComponent = CreateDefaultSubobject<UActorOptimizeSubjectComponent>(TEXT("OptimizeSubjectComp"));
	
	FarDistanceEffect_01->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "head");
	FarDistanceEffect_02->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "head");
	EnemyUIWidgetComp->SetupAttachment(GetMesh());
	
	EnemyUIWidgetComp->SetVisibility(false);
}

void APLAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 스킬 업데이트 타이머 
	GetWorld()->GetTimerManager().SetTimer(AiSkillTimerHandle, this, &APLAICharacter::UpdateSkill, 0.1f, true);

	// 플레이어와의 거리 체크 타이머 [플레이어의 빛 반경으로 들어와있는지 체크를 위해]
	GetWorld()->GetTimerManager().SetTimer(CheckDistancePlayerTimerHandle, this, &APLAICharacter::CheckDistanceToPlayer, 0.25f, true);

	// 위젯 변수 설정
	if(Cast<UPLWidgetBase>(EnemyUIWidgetComp->GetWidget()))
	{
		Cast<UPLWidgetBase>(EnemyUIWidgetComp->GetWidget())->OwnerPLCharacter = this;
	}
}

void APLAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APLAICharacter::DeadEvent()
{
	// 부모 함수 실행
	Super::DeadEvent();

	// 스킬 업데이트 타이머  해제
	if(CheckDistancePlayerTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CheckDistancePlayerTimerHandle);
	}
	// 플레이어와의 거리 체크 타이머 해제
	if(AiSkillTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(AiSkillTimerHandle);
	}
}

void APLAICharacter::BecomeTargetEvent()
{
	IPLTargetableInterface::BecomeTargetEvent();
	EnemyUIWidgetComp->SetVisibility(true);
}

void APLAICharacter::BecomeNonTargetEvent()
{
	IPLTargetableInterface::BecomeNonTargetEvent();
	EnemyUIWidgetComp->SetVisibility(false);
}


void APLAICharacter::UpdateSkill()
{
	//스킬 쿨타임 계산
	CalculateSkillColdTime();
	
	//전투 상태일 때만, 스킬 사용 여부 검사 및 스킬 사용
	if(CharacterState == ECharacterState::ECombat && !GetPLAnimationInstance()->Montage_IsPlaying(nullptr))
	{
		if(IsValid(CurrentTargetCharacter))
		{
			// 랜덤으로 스킬 인덱스 찝어서 검사
			const int _randomSkillIndex = GetRandomInt(0, SkillInfo.Num()-1);

			if(SkillInfo.IsValidIndex(_randomSkillIndex))
			{
				if(SkillInfo[_randomSkillIndex].ActivateSkillDistance >= GetDistanceFromCurrentTarget() &&				// 스킬 사용가능한 타겟과의 거리 검사
					SkillInfo[_randomSkillIndex].SkillColdTime <= SkillInfo[_randomSkillIndex].CurrentSkillColdTime &&  // 스킬 쿨타임 검사
					SkillInfo[_randomSkillIndex].ActivateSKillAngle >= GetAngleToTarget() &&							// 스킬 사용가능한 타겟과의 각도 검사
					ActionInfo.Contains(FGameplayTag::RequestGameplayTag("Action.Ai.RandomSkill")))					// 스킬 사용에 필요한 값을 ActionInfo가 가지고 있는지	검사		
				{
					// 스킬 사용을 위해 ActionInfo[Action.Ai.RandomSkill] 값 설정 
					ActionInfo[FGameplayTag::RequestGameplayTag("Action.Ai.RandomSkill")] = SkillInfo[_randomSkillIndex].PlayMontageAndAction;
					// 스킬 사용
					PlayAction(FGameplayTag::RequestGameplayTag("Action.Ai.RandomSkill"));
					// 사용한 스킬 쿨타임 초기화
					SkillInfo[_randomSkillIndex].CurrentSkillColdTime = 0.0f;
				}
			}
		}
	}
}

void APLAICharacter::CheckDistanceToPlayer()
{
	// 플레이어와의 거리가 가깝다면, 이펙트 off
	if(GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) < 900.0f)
	{
		if(FarDistanceEffect_01->IsActive())
		{
			FarDistanceEffect_01->Deactivate();
		}
		if(FarDistanceEffect_02->IsActive())
		{
			FarDistanceEffect_02->Deactivate();
		}
	}
	// 플레이어와의 거리가 멀다면, 이펙트 on
	else
	{
		if(FarDistanceEffect_01->IsActive() == false)
		{
			FarDistanceEffect_01->Activate();
		}
		if(FarDistanceEffect_02->IsActive()== false)
		{
			FarDistanceEffect_02->Activate();
		}
	}
}

void APLAICharacter::CalculateSkillColdTime()
{
	for(auto& _skillInfo : SkillInfo)
	{
		_skillInfo.CurrentSkillColdTime += 0.1f;
	}
}

float APLAICharacter::GetDistanceFromCurrentTarget() const
{
	if(IsValid(CurrentTargetCharacter))
	{
		return GetDistanceTo(CurrentTargetCharacter);
	}
	return -1.0f;
}

APLAiController* APLAICharacter::GetPLAiController() const
{
	return Cast<APLAiController>(GetController());
}

float APLAICharacter::GetAngleToTarget() const
{
	if (!GetCurrentTargetCharacter())
	{
		return 0.0f;
	}

	FVector Direction = GetCurrentTargetCharacter()->GetActorLocation() - GetActorLocation();
	Direction.Normalize();

	// Compute the angle between the two vectors
	const float DotProduct = FVector::DotProduct(GetActorForwardVector(), Direction);

	// Convert the angle from radians to degrees
	const float AngleInDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

	return AngleInDegrees;
}
