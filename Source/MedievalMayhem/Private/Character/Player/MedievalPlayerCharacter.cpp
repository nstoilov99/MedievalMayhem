// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/MedievalPlayerCharacter.h"
#include "Character/Player/MedievalPlayerState.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "AI/PlayerAIController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Player/MedievalPlayerController.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMedievalPlayerCharacter::AMedievalPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	AIControllerClass = APlayerAIController::StaticClass();
}

void AMedievalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AMedievalPlayerController* PlayerController = Cast<AMedievalPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MedievalMappingContext, 0);
		}
	}

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
}

void AMedievalPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMedievalPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMedievalPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMedievalPlayerCharacter::Jump);
	}

	//PlayerInputComponent->BindAxis("MoveForward", this, &AMedievalPlayerCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AMedievalPlayerCharacter::MoveRight);
	//PlayerInputComponent->BindAxis("LookUp", this, &AMedievalPlayerCharacter::LookUp);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &AMedievalPlayerCharacter::LookUpRate);
	//PlayerInputComponent->BindAxis("Turn", this, &AMedievalPlayerCharacter::Turn);
	//PlayerInputComponent->BindAxis("TurnRate", this, &AMedievalPlayerCharacter::TurnRate);

	BindASCInput();
}

void AMedievalPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMedievalPlayerState* PS = GetPlayerState<AMedievalPlayerState>();
	if (PS)
	{
		InitializeAbilityValues(PS);
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

USpringArmComponent* AMedievalPlayerCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* AMedievalPlayerCharacter::GetFollowCamera()
{
	return FollowCamera;
}

float AMedievalPlayerCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomArmLength;
}

FVector AMedievalPlayerCharacter::GetStartingCameraBoomLocation()
{
	return StartingCameraBoomLocation;
}

void AMedievalPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!IsAlive()) return;
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AMedievalPlayerCharacter::Look(const FInputActionValue& Value)
{
	if (!IsAlive()) return;
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AMedievalPlayerCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void AMedievalPlayerCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void AMedievalPlayerCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void AMedievalPlayerCharacter::TurnRate(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void AMedievalPlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
}

void AMedievalPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
}

void AMedievalPlayerCharacter::OnRep_PlayerState()
{
	AMedievalPlayerState* PS = GetPlayerState<AMedievalPlayerState>();
	if (PS)
	{
		InitializeAbilityValues(PS);
		BindASCInput();
	}
}

void AMedievalPlayerCharacter::InitializeAbilityValues(AMedievalPlayerState* PS)
{

	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	AttributeSetBase = PS->GetAttrubuteSetBase();

	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	InitializeAtrributes();
	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());
}

void AMedievalPlayerCharacter::BindASCInput()
{
	if (bASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("MedievalAbilityID"), static_cast<int32>(MedievalAbilityID::Confirm), static_cast<int32>(MedievalAbilityID::Cancel)));
		bASCInputBound = true;
	}
}
