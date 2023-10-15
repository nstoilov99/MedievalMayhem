// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDataStructs.h"
#include "EquipmentComponent.generated.h"

class UInventoryComponent;
class UItemBase;

UENUM()
enum class EEquipmentSlot : uint8
{
	ES_Head UMETA(DisplayName = "Head Slot"),
	ES_Necklace UMETA(DisplayName = "Necklace Slot"),
	ES_Chest UMETA(DisplayName = "Chest Slot"),
	ES_Gloves UMETA(DisplayName = "Gloves Slot"),
	ES_Ring1 UMETA(DisplayName = "Ring Slot 1"),
	ES_Ring2 UMETA(DisplayName = "Ring Slot 2"),
	ES_Pants UMETA(DisplayName = "Pants Slot"),
	ES_Boots UMETA(DisplayName = "Boots Slot"),
	ES_Weapon UMETA(DisplayName = "Weapon Slot"),
	ES_Offhand UMETA(DisplayName = "Offhand Slot"),
	ES_MAX UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EEquipmentSlot, EEquipmentSlot::ES_MAX);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALMAYHEM_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UEquipmentComponent();

	void HandleEquipItem(UItemBase* InItem);
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	TMap<EEquipmentSlot, TObjectPtr<UItemBase>> PlayerEquipment;

	void InitializeEquipmentSlots();
};
