// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWeapon::AWeapon()
{

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	ShowInteractionWidget(false);
}

void AWeapon::ShowInteractionWidget(bool bShowWidget)
{
	if (ItemWidget)
	{
		ItemWidget->SetVisibility(true);
	}
}