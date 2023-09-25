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

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(ItemMesh);

	ItemMesh->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionResponseToChannel(ECC_Interactable, ECollisionResponse::ECR_Block);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ItemWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	ItemWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}