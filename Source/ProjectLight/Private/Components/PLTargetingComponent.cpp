// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PLTargetingComponent.h"
#include "GameFramework/Character.h"
#include "Interface/PLTargetableInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UPLTargetingComponent::UPLTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPLTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPLTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(IsValid(CurrentTarget))
	{
		FVector _targetVector = CurrentTarget->GetActorLocation();

		// 캐릭터가 타겟팅 대상이고,  Mesh에 소켓 중 TargetSock 이라는 이름의 소켓을 갖고 있다면, 그곳을 타겟팅 하도록 
		if(Cast<ACharacter>(CurrentTarget) && Cast<ACharacter>(CurrentTarget)->GetMesh()->GetAllSocketNames().Contains("TargetSock"))
		{
			_targetVector = Cast<ACharacter>(CurrentTarget)->GetMesh()->GetSocketLocation("TargetSock");
		}
		_targetVector.Z -= 150;
		
		FRotator _rot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), _targetVector);
		FRotator _lookAtRot = UKismetMathLibrary::RInterpTo(GetPlayerController()->K2_GetActorRotation(), _rot, GetWorld()->GetDeltaSeconds(), 5);

		FRotator _goalRot = _lookAtRot;
		_goalRot.Roll = GetPlayerController()->K2_GetActorRotation().Roll;

		GetPlayerController()->SetControlRotation(_lookAtRot);
	}
}

APlayerController* UPLTargetingComponent::GetPlayerController()
{
	if(!PlayerController)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetOwner(), 0);
	}
	return PlayerController;
}

void UPLTargetingComponent::ToggleTargeting()
{
	if(IsValid(CurrentTarget))
	{
		SetTarget(nullptr);
	}
	else
	{
		ActivateTargeting();
	}
}

void UPLTargetingComponent::SetTarget(AActor* _target)
{
	// 새로운 적으로 타겟팅 하기전, 이미 타겟팅해놓은 적이 있다면, 그 적의 타겟팅 해제 이벤트 호출
	if(IsValid(CurrentTarget))
	{
		// 타겟팅 해제 이벤트 호출
		IPLTargetableInterface* _targetable = Cast<IPLTargetableInterface>(CurrentTarget);
		if(_targetable)
		{
			_targetable->BecomeNonTargetEvent();
		}
	}
	
	
	if(_target == nullptr)
	{
		CurrentTarget = nullptr;
		return;
	}

	// TargetableInterface를 갖고 있다면 타겟팅
	if(IPLTargetableInterface* _targetable =Cast<IPLTargetableInterface>(_target))
	{
		CurrentTarget = _target;

		// 타겟팅 획득 이벤트 호출
		_targetable->BecomeTargetEvent();
		
		return;
	}

	
	CurrentTarget = nullptr;
}


void UPLTargetingComponent::ActivateTargeting()
{
	// 타겟 가능한 오브젝트들을 찾아서 AvailableTargetArray 에 추가
	PopulatePotentialTargetsArray();

	AActor* _currentTarget = nullptr;
	FVector _cameraForwardVector = UKismetMathLibrary::GetForwardVector(UGameplayStatics::GetPlayerCameraManager(GetOwner(),0)->GetCameraRotation());

	_cameraForwardVector.Z = 0;
	_cameraForwardVector = _cameraForwardVector.GetSafeNormal();
	float _maxDistance = 2000.0f + 100.0f;
	
	for(AActor* _target : AvailableTargetArray)
	{
		float distance = _target->GetDistanceTo(GetOwner());
		if(distance < _maxDistance && GetTargetDegree(_target) < 70.0f)
		{
			if (distance < _maxDistance)
			{
				_currentTarget = _target;
				_maxDistance = distance;
			}
		}
	}

	if(_currentTarget)
	{
		SetTarget(_currentTarget);	
	}
}

void UPLTargetingComponent::PopulatePotentialTargetsArray()
{
	AvailableTargetArray.Empty();
	TArray<AActor*> ignoredActorArray;
	
	UKismetSystemLibrary::SphereOverlapActors(this, GetOwner()->GetActorLocation(),
			2000.0f, ObjectsToQuery, AActor::StaticClass(), ignoredActorArray, AvailableTargetArray);

	//Attach 되어 있는 엑터 삭제
	for(int i = 0; i < AvailableTargetArray.Num(); ++i)
	{
		AvailableTargetArray.RemoveAll([](AActor* _target)
		{
			return _target->GetAttachParentActor() != nullptr;
		});
	}

	// interface 검사
	for(int i = 0; i < AvailableTargetArray.Num(); ++i)
	{
		if(!AvailableTargetArray[i]->GetClass()->ImplementsInterface(UPLTargetableInterface::StaticClass()))
		{
			AvailableTargetArray.RemoveAt(i);
		}
	}

	
}


float UPLTargetingComponent::GetTargetDegree(AActor* _target)
{
	if(IsValid( _target))
	{
		FVector _ownerLoc = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
		FRotator _findLookRot = UKismetMathLibrary::FindLookAtRotation(_ownerLoc, _target->GetActorLocation());
		FVector _lookRotFowardVector = UKismetMathLibrary::GetForwardVector(_findLookRot);
		const float _dot = UKismetMathLibrary::Dot_VectorVector(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector(), _lookRotFowardVector);
		const float _angle  = UKismetMathLibrary::DegAcos(_dot);
		return _angle;
	}
	
	return 0.0f;
}



