// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

/**
 * 
 */
UENUM()
enum class EItemType : uint8
{
	EIT_Gear UMETA(DisplayName = "Gear"),
	EIT_Consumable UMETA(DisplayName = "Consumable"),
	EIT_Material UMETA(DisplayName = "Material"),
	EIT_Quest UMETA(DisplayName = "Quest")
};

UENUM()
enum class EGearType : uint8
{
	EGST_None UMETA(DisplayName = "None"),
	EGST_Head UMETA(DisplayName = "Head"),
	EGST_Necklace UMETA(DisplayName = "Necklace"),
	EGST_Shoulders UMETA(DisplayName = "Shoulders"),
	EGST_Chest UMETA(DisplayName = "Chest"),
	EGST_Gloves UMETA(DisplayName = "Gloves"),
	EGST_Ring UMETA(DisplayName = "Ring"),
	EGST_Pants UMETA(DisplayName = "Pants"),
	EGST_Boots UMETA(DisplayName = "Boots"),
	EGST_Offhand UMETA(DisplayName = "Offhand"),
	EGST_Weapon UMETA(DisplayName = "Weapon"),
	EGST_Weapon2H UMETA(DisplayName = "Two Handed Weapon")
};

UENUM()
enum class EItemQuality : uint8
{
	EIQ_Common UMETA(DisplayName = "Common"),
	EIQ_Uncommon UMETA(DisplayName = "Uncommon"),
	EIQ_Rare UMETA(DisplayName = "Rare"),
	EIQ_Epic UMETA(DisplayName = "Epic"),
	EIQ_Legendary UMETA(DisplayName = "Legendary")
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText InteractionText;

	UPROPERTY(EditAnywhere)
	FText HoldInteractionText;

	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EGearType GearType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;
};