// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MedievalPlayerCharacter.h"
#include "UI/HUD/MedievalHUD.h"
#include "Player/MedievalPlayerState.h"
#include "Player/MedievalPlayerController.h"
#include "Items/Pickup.h"
#include "Items/Equipment.h"
#include "UI/Widgets/Inventory/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MedievalAbilitySystemComponent.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkeletalMeshSocket.h"
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

	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(20);
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

void AMedievalPlayerCharacter::EquipWeapon(AEquipment* WeaponToEquip)
{
	if (EquippedWeapon)
	{
		return;
	}

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);

	const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("WeaponSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(EquippedWeapon, GetMesh());
	}
	EquippedWeapon->SetOwner(this);
}

void AMedievalPlayerCharacter::DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop)
{
	if (PlayerInventory->FindMatchingItem(ItemToDrop))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector SpawnLocation{ GetActorLocation() + (GetActorForwardVector() * 50.f) };
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		const int32 RemovedQuantity = PlayerInventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		APickup* Pickup = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);

		Pickup->InitializeDrop(ItemToDrop, RemovedQuantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was somehow null!"));
	}
}

bool AMedievalPlayerCharacter::IsWeaponEquipped() const
{
	if (EquippedWeapon)
	{
		return true;
	}
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