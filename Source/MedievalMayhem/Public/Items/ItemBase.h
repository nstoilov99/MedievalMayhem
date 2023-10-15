// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"

class AMedievalPlayerCharacter;
class UInventoryComponent;
class UEquipmentComponent;
class USphereComponent;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	TObjectPtr<UInventoryComponent> OwningInventory;

	UPROPERTY()
	TObjectPtr<UEquipmentComponent> OwningEquipment;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EGearType GearType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData NumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData AssetData;

	bool bIsCopy;
	bool bIsPickup;

	/*
	* Functions
	*/

	UItemBase();

	void ResetItemFlags();

	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStack() const { return Quantity; }

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; }

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(AMedievalPlayerCharacter* Character);


protected:
	bool operator==(const FName& OtherID)const
	{
		return this->ID == OtherID;
	}
};
