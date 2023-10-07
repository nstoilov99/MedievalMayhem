// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MedievalPlayerCharacter.h"
#include "Player/MedievalPlayerController.h"
#include "Player/MedievalPlayerState.h"
#include "UI/HUD/MedievalHUD.h"
#include "Interfaces/InteractionInterface.h"
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
	HUD = Cast<AMedievalHUD>(GetHUD());
}

void AMedievalPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TimeSince(LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		TraceInteractable();
	}
}

void AMedievalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UMedievalInputComponent* MedievalInputComponent = CastChecked<UMedievalInputComponent>(InputComponent);

	MedievalInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMedievalPlayerController::Move);
	MedievalInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMedievalPlayerController::Look);
	MedievalInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMedievalPlayerController::Jump);
	MedievalInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMedievalPlayerController::BeginInteract);
	MedievalInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AMedievalPlayerController::EndInteract);
	MedievalInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AMedievalPlayerController::ToggleMenu);
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
	
	TraceInteractable();
}

void AMedievalPlayerController::Jump()
{
	AMedievalPlayerCharacter* MedievalCharacter = Cast<AMedievalPlayerCharacter>(GetPawn());
	if (MedievalCharacter)
	{
		MedievalCharacter->Jump();
	}
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

void AMedievalPlayerController::TraceInteractable()
{
	if (AMedievalPlayerCharacter* PlayerCharacter = Cast<AMedievalPlayerCharacter>(GetPawn()))
	{
		LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

		FVector TraceLocationStart;
		FRotator TraceRotation;
		GetPlayerViewPoint(TraceLocationStart, TraceRotation);
		FVector TraceLocationEnd = TraceLocationStart + UKismetMathLibrary::GetForwardVector(TraceRotation) * TraceScale;

		FHitResult HitResult;
		bool Hit = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(), TraceLocationStart, TraceLocationEnd, TraceSphereRadius,
			UEngineTypes::ConvertToTraceType(ECC_Interactable), false, TraceActorsToIgnore,
			EDrawDebugTrace::None, HitResult, true);
		
		if (Hit)
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{
				bIsInteracting = true;

				if (HitResult.GetActor() != CurrentInteractable)
				{
					FoundInteractable(HitResult.GetActor());
					return;
				}
				if (HitResult.GetActor() == CurrentInteractable)
				{
					return;
				}
			}
		}
		NoInteractableFound();
	}
}

void AMedievalPlayerController::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (CurrentInteractable)
	{
		TargetInteractable = CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();
}

void AMedievalPlayerController::NoInteractableFound()
{
	if (IsInteracting())
	{
		bIsInteracting = false;
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		HUD->HideInteractionWidget();

		CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void AMedievalPlayerController::BeginInteract()
{
	TraceInteractable();

	if (CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&AMedievalPlayerController::Interact,
					TargetInteractable->InteractableData.InteractionDuration,
					false);
			}
		}
	}
}

void AMedievalPlayerController::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		if (AMedievalPlayerCharacter* PlayerCharacter = Cast<AMedievalPlayerCharacter>(GetPawn()))
		{
			TargetInteractable->Interact(PlayerCharacter);
		}
	}
}

void AMedievalPlayerController::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void AMedievalPlayerController::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

void AMedievalPlayerController::ToggleMenu()
{
	if (HUD)
	{
		HUD->ToggleInventory();
	}
}

void AMedievalPlayerController::OnMatchStateSet(FName State)
{
}

