// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Inventory/InventoryTooltip.h"
#include "UI/Widgets/Inventory/InventoryItemSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"

void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();

	switch (ItemBeingHovered->ItemType)
	{
	case EItemType::EIT_Gear:
		ItemType->SetText(FText::FromString("Gear"));
		DamageValue->SetVisibility(ESlateVisibility::Visible);
		StrengthValue->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::EIT_Consumable:
		ItemType->SetText(FText::FromString("Consummable"));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		StrengthValue->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::EIT_Material:
		
		break;
	case EItemType::EIT_Quest:
		break;
	default:
		break;
	}
	ItemName->SetText(ItemBeingHovered->TextData.Name);
	UsageText->SetText(ItemBeingHovered->TextData.UsageText);

	if (ItemBeingHovered->NumericData.bIsStackable)
	{
		MaxStackSize->SetText(FText::AsNumber(ItemBeingHovered->NumericData.MaxStackSize));
	}
	else
	{
		MaxStackSize_HBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}
