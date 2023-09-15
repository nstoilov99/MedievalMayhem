// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/MedievalAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/MedievalPlayerCharacter.h"

void UMedievalAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MedievalCharacter = Cast<AMedievalPlayerCharacter>(TryGetPawnOwner());
}

void UMedievalAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	MedievalCharacter == nullptr ? Cast<AMedievalPlayerCharacter>(TryGetPawnOwner()) : MedievalCharacter;

	if (MedievalCharacter == nullptr) return;

	FVector Velocity = MedievalCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
	SpeedSmoothed = FMath::FInterpTo(SpeedSmoothed, Speed, DeltaTime, 10.f);

	Direction = CalculateDirection(Velocity, MedievalCharacter->GetActorRotation());
	DirectionSmoothed = FMath::FInterpTo(DirectionSmoothed, Direction, DeltaTime, 10.f);

	bIsInAir = MedievalCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = MedievalCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
}
