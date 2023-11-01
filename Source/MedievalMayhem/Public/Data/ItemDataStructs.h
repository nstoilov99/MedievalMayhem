// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilitySystem/MedievalAttributeSet.h"
#include "ItemDataStructs.generated.h"

class UMedievalAttributeSet;
class UGameplayEffect;
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
	EGST_Head UMETA(DisplayName = "Head"),
	EGST_Necklace UMETA(DisplayName = "Necklace"),
	EGST_Chest UMETA(DisplayName = "Chest"),
	EGST_Gloves UMETA(DisplayName = "Gloves"),
	EGST_Ring UMETA(DisplayName = "Ring"),
	EGST_Pants UMETA(DisplayName = "Pants"),
	EGST_Boots UMETA(DisplayName = "Boots"),
	EGST_Weapon1H UMETA(DisplayName = "One Handed Weapon"),
	EGST_Weapon2H UMETA(DisplayName = "Two Handed Weapon"),
	EGST_MainHand UMETA(DisplayName = "Main Handed Weapon"),
	EGST_Offhand UMETA(DisplayName = "Offhand"),
	EGST_MAX UMETA(Hidden)
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

//USTRUCT()
//struct FEquipmentAttributeData 
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere)
//	FGameplayAttribute Attribute;
//
//	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
//	float MinValue;
//
//	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
//	float MaxValue;
//};

USTRUCT()
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize = 1;

	UPROPERTY(EditAnywhere)
	bool bIsStackable = false;
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
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data", meta = (EditCondition = "ItemType == EItemType::EIT_Gear", EditConditionHides))
	EGearType GearType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	//UPROPERTY(EditAnywhere, Category = "Item Data", meta = (EditCondition = "ItemType == EItemType::EIT_Gear", EditConditionHides))
	//TArray<FEquipmentAttributeData> AttributeData;

	UPROPERTY(EditAnywhere, Category = "Item Data", meta = (EditCondition = "ItemType == EItemType::EIT_Gear", EditConditionHides))
	TArray<TObjectPtr<UGameplayEffect>> AttributeData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data", meta = (EditCondition = "ItemType != EItemType::EIT_Gear", EditConditionHides))
	FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;
};