// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemSlotsByTypes.h"

UItemSlotsByTypes::UItemSlotsByTypes()
{
	for (EGearType Type : TEnumRange<EGearType>())
	{
		FSlotsByTypes SlotsByType;
		SlotsByType.GearType = Type;
		SlotsByTypes.Add(SlotsByType);
	}
}

EEquipmentSlot UItemSlotsByTypes::GetFirstSlot(EGearType ItemType)
{
	for (FSlotsByTypes SlotsByType : SlotsByTypes)
	{
		if (SlotsByType.GearType == ItemType)
		{
			return SlotsByType.ItemSlots[0];
		}
	}
	return EEquipmentSlot::ES_None;
}

TArray<EEquipmentSlot> UItemSlotsByTypes::GetSlots(EGearType ItemType)
{
	for (FSlotsByTypes SlotsByType : SlotsByTypes)
	{
		if (SlotsByType.GearType == ItemType)
		{
			return SlotsByType.ItemSlots;
		}
	}
	return TArray<EEquipmentSlot>();
}
