// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MedievalPlayerCharacter.h"
#include "UI/HUD/MedievalHUD.h"
#include "Player/MedievalPlayerState.h"
#include "Player/MedievalPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MedievalAbilitySystemComponent.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"

AMedievalPlayerCharacter::AMedievalPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.f;

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}

void AMedievalPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor infro for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AMedievalPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

bool AMedievalPlayerCharacter::IsWeaponEquipped()
{
	return false;
}

void AMedievalPlayerCharacter::InitAbilityActorInfo()
{
	AMedievalPlayerState* MedievalPlayerState = GetPlayerState<AMedievalPlayerState>();
	check(MedievalPlayerState);
	MedievalPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MedievalPlayerState, this);
	Cast<UMedievalAbilitySystemComponent>(MedievalPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = MedievalPlayerState->GetAbilitySystemComponent();
	AttributeSet = MedievalPlayerState->GetAttributeSet();

	if (AMedievalPlayerController* MedievalPlayerController = Cast<AMedievalPlayerController>(GetController()))
	{
		if (AMedievalHUD* MedievalHUD = Cast<AMedievalHUD>(MedievalPlayerController->GetHUD()))
		{
			MedievalHUD->InitOverlay(MedievalPlayerController, MedievalPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}