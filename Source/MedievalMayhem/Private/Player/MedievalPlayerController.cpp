// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MedievalPlayerCharacter.h"
#include "Player/MedievalPlayerController.h"
#include "Player/MedievalPlayerState.h"
#include "Interaction/InteractionInterface.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Input/MedievalInputComponent.h"
#include "GameModes/MedievalGameMode.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AbilitySystemComponent.h"


AMedievalPlayerController::AMedievalPlayerController()
{
	bReplicates = true;
}

void AMedievalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MedievalContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(MedievalContext, 0);
	}
}

void AMedievalPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMedievalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UMedievalInputComponent* MedievalInputComponent = CastChecked<UMedievalInputComponent>(InputComponent);

	MedievalInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMedievalPlayerController::Move);
	MedievalInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMedievalPlayerController::Look);
	MedievalInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMedievalPlayerController::Jump);
	MedievalInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMedievalPlayerController::Interact);
	MedievalInputComponent->BindAbilityActions(AbilityInputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AMedievalPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AMedievalPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	GetPawn()->AddControllerPitchInput(LookAxisVector.Y);
	GetPawn()->AddControllerYawInput(LookAxisVector.X);
	
	TracePlayerInteractable();
}

void AMedievalPlayerController::Jump()
{
	AMedievalPlayerCharacter* MedievalCharacter = Cast<AMedievalPlayerCharacter>(GetPawn());
	if (MedievalCharacter)
	{
		MedievalCharacter->Jump();
	}
}

void AMedievalPlayerController::Interact()
{

}

void AMedievalPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void AMedievalPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
}

void AMedievalPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
}

void AMedievalPlayerController::TracePlayerInteractable()
{
	if (AMedievalPlayerCharacter* PlayerCharacter = Cast<AMedievalPlayerCharacter>(GetPawn()))
	{
		FVector TraceLocationStart;
		FRotator TraceRotation;
		GetPlayerViewPoint(TraceLocationStart, TraceRotation);
		FVector TraceLocationEnd = TraceLocationStart + UKismetMathLibrary::GetForwardVector(TraceRotation) * TraceScale;

		FHitResult HitResult;
		TArray<AActor*> ActorToIgnore;
		bool Hit = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(), TraceLocationStart, TraceLocationEnd, TraceSphereRadius,
			UEngineTypes::ConvertToTraceType(ECC_Interactable), false, ActorToIgnore,
			EDrawDebugTrace::None, HitResult, true);

		IInteractionInterface* Interaction = Cast<IInteractionInterface>(HitResult.GetActor());
		if (Hit && Interaction)
		{
			Interaction->ShowInteractionWidget(true);
			LastInteraction = Interaction;
		}
		if (!Hit || Interaction == nullptr)
		{
			LastInteraction->ShowInteractionWidget(false);
		}
	}
}

void AMedievalPlayerController::OnMatchStateSet(FName State)
{
}
