// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Inventory/InventoryItemSlot.h"
#include "UI/Widgets/Inventory/DragItemVisual.h"
#include "UI/Widgets/Inventory/ItemDragDropOperation.h"
#include "UI/Widgets/Inventory/InventoryTooltip.h"
#include "Character/MedievalPlayerCharacter.h"
#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

AMedievalPlayerCharacter* UInventoryItemSlot::GetPlayerCharacter()
{
    if (ItemReference->OwningInventory)
    {
        return Cast<AMedievalPlayerCharacter>(ItemReference->OwningInventory->GetOwner());
    }
    return nullptr;
}

void UInventoryItemSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (TooltipClass)
    {
        UInventoryTooltip* Tooltip = CreateWidget<UInventoryTooltip>(this, TooltipClass);
        Tooltip->InventorySlotBeingHovered = this;
        SetToolTip(Tooltip);
    }
}

void UInventoryItemSlot::NativeConstruct()
{
    Super::NativeConstruct();

    if (ItemReference)
    {
        switch (ItemReference->ItemQuality)
        {
        case EItemQuality::EIQ_Common:
            ItemBorder->SetBrushColor(FLinearColor::Gray);
            break;
        case EItemQuality::EIQ_Uncommon:
            ItemBorder->SetBrushColor(FLinearColor::Green);
            break;
        case EItemQuality::EIQ_Rare:
            ItemBorder->SetBrushColor(FLinearColor::Blue);
            break;
        case EItemQuality::EIQ_Epic:
            ItemBorder->SetBrushColor(FColor::Purple);
            break;
        case EItemQuality::EIQ_Legendary:
            ItemBorder->SetBrushColor(FColor::Orange);
            break;
        default:
            break;
        }

        ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

        if (ItemReference->NumericData.bIsStackable)
        {
            ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
            ItemQuantity->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }
    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        if (ItemReference->ItemType == EItemType::EIT_Gear)
        {

        }
    }
    
    //submenu on right click will happen here

    return Reply.Unhandled();
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    if (DragItemVisualClass)
    {
        const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
        DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
        DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());
        DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

        UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
        DragItemOperation->SourceItem = ItemReference;
        DragItemOperation->SourceInventory = ItemReference->OwningInventory;

        DragItemOperation->DefaultDragVisual = DragVisual;
        DragItemOperation->Pivot = EDragPivot::TopLeft;

        OutOperation = DragItemOperation;
    }
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
