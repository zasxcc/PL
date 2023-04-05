// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PLAnimationInstance.h"
#include "Character/PLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPLAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	//Set OwnerPLCharacter 
	if(TryGetPawnOwner())
	{
		if(Cast<APLCharacter>(TryGetPawnOwner()))
		{
			OwnerPLCharacter = Cast<APLCharacter>(TryGetPawnOwner());
		}
	}
	
}

void UPLAnimationInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	if(IsValid(GetOwnerPLCharacter()))
	{
		// IsMove?
		if(GetOwnerPLCharacter()->GetVelocity().Length() > 0.0f)
		{
			IsMove = true;
		}
		else
		{
			IsMove = false;
		}

		//Update Velocity, CharacterSpeed, NormalizedSpeed, Rotation 
		Velocity = GetOwnerPLCharacter()->GetVelocity();
		CharacterSpeed = Velocity.Size();
		NormalizedSpeed = CharacterSpeed / GetOwnerPLCharacter()->GetCharacterMovement()->GetMaxSpeed();
		Rotation = GetOwnerPLCharacter()->GetActorRotation();

		//Update Direction
		if (!Velocity.IsNearlyZero())
		{
			const FMatrix RotMatrix = FRotationMatrix(Rotation);
			const FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
			const FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
			const FVector NormalizedVel = Velocity.GetSafeNormal2D();

			// Get a cos(alpha) of forward vector vs velocity
			const float ForwardCosAngle = FVector::DotProduct(ForwardVector, NormalizedVel);
			// Get the alpha and convert to degree
			float ForwardDeltaDegree = FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));
			// Depending on where right vector is, flip it
			const float RightCosAngle = FVector::DotProduct(RightVector, NormalizedVel);
			if (RightCosAngle < 0)
			{
				ForwardDeltaDegree *= -1;
			}

			Direction = ForwardDeltaDegree;
		}
		else
		{
			Direction = 0.0f;
		}

		//Update HasVelocity
		FVector _2dVector;
		_2dVector.X = 1.0f;
		_2dVector.Y = 1.0f;
		_2dVector.Z = 0.0f;
		if(UKismetMathLibrary::Vector_IsNearlyZero(Velocity*_2dVector))
		{
			HasVelocity = false;
		}
		else
		{
			HasVelocity = true;
		}

		//Update HasAccelerate
		if(UKismetMathLibrary::Vector_IsNearlyZero(GetOwnerPLCharacter()->GetCharacterMovement()->GetCurrentAcceleration() * _2dVector))
		{
			HasAccelerate = false;
		}
		else
		{
			HasAccelerate = true;
		}
	}
	
}
