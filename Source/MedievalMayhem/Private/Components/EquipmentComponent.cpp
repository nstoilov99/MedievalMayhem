// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentComponent.h"
#include "Data/ItemSlotsByTypes.h"
#include "Items/ItemBase.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InitializeEquipmentSlots();
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEquipmentComponent::HandleEquipItem(UItemBase* InItem)
{
	if (GetOwner())
	{
		if (InItem->ItemType == EItemType::EIT_Gear)
		{
			EEquipmentSlot FirstSlot = SlotsByTypes->GetFirstSlot(InItem->GearType);
			if (FirstSlot != EEquipmentSlot::ES_None)
			{
				PlayerEquipment[FirstSlot] = InItem;
			}
		}
	}
}


void UEquipmentComponent::InitializeEquipmentSlots()
{
	for(EEquipmentSlot Slot : TEnumRange<EEquipmentSlot>())
	{
		PlayerEquipment.Add(Slot);
	}
}
