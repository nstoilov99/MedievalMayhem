// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Inventory/InventoryMenuWidget.h"
#include "UI/Widgets/Inventory/ItemDragDropOperation.h"
#include "Character/MedievalPlayerCharacter.h"
#include "Items/ItemBase.h"

void UInventoryMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInventoryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayerCharacter = Cast<AMedievalPlayerCharacter>(GetOwningPlayerPawn());
}

bool UInventoryMenuWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);
	if (PlayerCharacter && ItemDragDrop->SourceItem)
	{
		PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		return true;
	}
	return false;
}
