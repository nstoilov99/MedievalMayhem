// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/EquipmentComponent.h"
#include "ItemDataStructs.h"
#include "ItemSlotsByTypes.generated.h"


USTRUCT(BlueprintType)
struct FSlotsByTypes 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EGearType GearType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<EEquipmentSlot> ItemSlots;
};
ENUM_RANGE_BY_COUNT(EGearType, EGearType::EGST_MAX);
/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UItemSlotsByTypes : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UItemSlotsByTypes();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSlotsByTypes> SlotsByTypes;

	UFUNCTION()
	EEquipmentSlot GetFirstSlot(EGearType ItemType);

	UFUNCTION()
	TArray<EEquipmentSlot> GetSlots(EGearType ItemType);
};
