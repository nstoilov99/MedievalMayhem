// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Equipment.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "Character/MedievalPlayerCharacter.h"
#include "Player/MedievalPlayerController.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEquipment::AEquipment()
{

}

void AEquipment::SetWeaponState(EWeaponState State)
{
	WeaponState = State;
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		ShowInteractionWidget(false);
		Mesh->SetSimulatePhysics(false);
		Mesh->SetEnableGravity(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToChannel(ECC_Interactable, ECollisionResponse::ECR_Ignore);
		EnableCustomDepth(false);
		break;
	case EWeaponState::EWS_Pickedup:
		ShowInteractionWidget(false);
		Mesh->SetSimulatePhysics(false);
		Mesh->SetEnableGravity(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		EnableCustomDepth(false);
		break;
	case EWeaponState::EWS_Dropped:
		Mesh->SetSimulatePhysics(true);
		Mesh->SetEnableGravity(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RARE);
		Mesh->MarkRenderStateDirty();
		EnableCustomDepth(true);
		break;
	default:
		break;
	}
}

// Called when the game starts or when spawned
void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	InteractableData = InstanceInteractableData;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);
	ShowInteractionWidget(false);
}

void AEquipment::ShowInteractionWidget(bool bShowWidget)
{
	if (ItemWidget)
	{
		ItemWidget->SetVisibility(bShowWidget);
	}
}

void AEquipment::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
		Mesh->SetCustomDepthStencilValue(252.f);
		ShowInteractionWidget(true);
	}
}

void AEquipment::EndFocus()
{
	if (Mesh)
	{
		ShowInteractionWidget(false);
		Mesh->SetRenderCustomDepth(false);
	}
}

void AEquipment::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on Weapon actor"));
}

void AEquipment::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract override on Weapon actor"));
}

void AEquipment::Interact(AMedievalPlayerCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on Weapon actor"));
	if (PlayerCharacter)
	{
		PlayerCharacter->EquipWeapon(this);
		if (AMedievalPlayerController* PlayerController = Cast<AMedievalPlayerController>(PlayerCharacter->Controller))
		{
			PlayerController->AddToActorsToIgnore(this);
		}
	}
}
