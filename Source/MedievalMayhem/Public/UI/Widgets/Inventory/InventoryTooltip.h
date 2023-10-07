// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

class UInventoryItemSlot;
class UHorizontalBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UInventoryItemSlot> InventorySlotBeingHovered;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UTextBlock> ItemName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemType;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DamageValue;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StrengthValue;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> UsageText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescription;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxStackSize;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> MaxStackSize_HBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SellValue;
protected:

	virtual void NativeConstruct() override;
};
