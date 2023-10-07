// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Interactable, ECollisionResponse::ECR_Block);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetEnableGravity(true);

	ItemWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	ItemWidget->SetupAttachment(RootComponent);
}

void AItem::EnableCustomDepth(bool bEnable)
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(bEnable);
	}
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemWidget)
	{
		ItemWidget->SetVisibility(false);
	}
}