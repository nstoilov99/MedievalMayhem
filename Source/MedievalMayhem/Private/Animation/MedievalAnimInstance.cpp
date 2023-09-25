// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MedievalAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/MedievalPlayerCharacter.h"

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

	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, MedievalCharacter->GetActorRotation());
	DirectionSmoothed = FMath::FInterpTo(DirectionSmoothed, Direction, DeltaTime, 10.f);

	bIsInAir = MedievalCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = MedievalCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;

	bWeaponEquipped = MedievalCharacter->IsWeaponEquipped();
	if (bWeaponEquipped && MedievalCharacter->GetWeapon())
	{
		LeftHandTransform = MedievalCharacter->GetWeapon()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		MedievalCharacter->GetMesh()->TransformFromBoneSpace(FName("Wrist_R"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
	}
}
