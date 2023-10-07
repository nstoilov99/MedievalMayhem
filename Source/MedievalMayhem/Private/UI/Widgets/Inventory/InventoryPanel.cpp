// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Inventory/InventoryPanel.h"
#include "UI/Widgets/Inventory/InventoryItemSlot.h"
#include "UI/Widgets/Inventory/ItemDragDropOperation.h"
#include "UI/Widgets/Inventory/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Character/MedievalPlayerCharacter.h"

void UInventoryPanel::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    PlayerCharacter = Cast<AMedievalPlayerCharacter>(GetOwningPlayerPawn());
    if (PlayerCharacter)
    {
        InventoryReference = PlayerCharacter->GetInventory();
        if (InventoryReference)
        {
            InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPanel::RefreshInventory);
            SetInfoText();
        }
    }
}
void UInventoryPanel::SetInfoText()
{
    CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
        InventoryReference->GetInventoryContents().Num(),
        InventoryReference->GetSlotsCapacity()));
}

void UInventoryPanel::RefreshInventory()
{
    if (InventoryReference && InventorySlotClass)
    {
        InventoryWrapBox->ClearChildren();
        for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
        {
            UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotClass);
            ItemSlot->SetItemReference(InventoryItem);

            InventoryWrapBox->AddChildToWrapBox(ItemSlot);
        }
        SetInfoText();
    }
}

bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);
    if (ItemDragDrop->SourceItem && InventoryReference)
    {
        //returning true will stop the drop operation at this widget
        return true;
    }
    // returning false will cause the drop operation to fall through to underlying widgets (if any)
    return false;
}
