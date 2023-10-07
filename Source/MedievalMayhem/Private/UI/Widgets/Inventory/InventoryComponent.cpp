// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Inventory/InventoryComponent.h"
#include "Items/ItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* InItem) const
{
	if (InItem)
	{
		if (InventoryContents.Contains(InItem))
		{
			return InItem;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* InItem) const
{
	if (InItem)
	{
		if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(InItem))
		{
			return *Result;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* InItem) const
{
	if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = 
		InventoryContents.FindByPredicate(
			[&InItem](const UItemBase* InventoryItem) 
			{
				return InventoryItem->ID == InItem->ID && !InventoryItem->IsFullItemStack();
			}
		))
	{
		return *Result;
	}
	return nullptr;
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequestedAddAmount)
{
	const int32 AddAmountToMakeFullStack = StackableItem->NumericData.MaxStackSize - StackableItem->Quantity;

	return FMath::Min(InitialRequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove)
{
	InventoryContents.RemoveSingle(ItemToRemove);
	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* InItem, int32 DesiredAmountToRemove)
{
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, InItem->Quantity);

	InItem->SetQuantity(InItem->Quantity - ActualAmountToRemove);

	OnInventoryUpdated.Broadcast();

	return ActualAmountToRemove;

}

void UInventoryComponent::SplitExistingStack(UItemBase* InItem, const int32 AmountToSplit)
{
	if (!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
	{
		RemoveAmountOfItem(InItem, AmountToSplit);
		AddNewItem(InItem, AmountToSplit);
	}
}

FItemAddResult UInventoryComponent::HandleNonStackableItems(UItemBase* InItem)
{
	if (InventoryContents.Num() + 1 > InventorySlotsCapacity)
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Inventory is full, or invalid item."), InItem->TextData.Name));
	}

	AddNewItem(InItem, 1);
	return FItemAddResult::AddedAll(1 , FText::Format(FText::FromString("Successfully added {0} x{1} to the inventory."), InItem->TextData.Name, InItem->Quantity));
}

int32 UInventoryComponent::HandleStackableItems(UItemBase* InItem, int32 RequestedAddAmount)
{
	if (RequestedAddAmount <= 0)
	{
		//invalid item data
		return 0;
	}

	int32 AmountToDistribute = RequestedAddAmount;
	// check if the input item already exists in the inventory and is not a full stack
	UItemBase* ExistingItem = FindNextPartialStack(InItem);

	// distribute stack over existing stacks
	while (ExistingItem)
	{
		//calculate how many of the existing item would be needed to make the next full stack
		const int32 AmountToMakeFullstack = CalculateNumberForFullStack(ExistingItem, AmountToDistribute);

		//check if the amount to make a full stack is less the amount we want to add
		if (AmountToMakeFullstack < AmountToDistribute)
		{
			ExistingItem->SetQuantity(ExistingItem->Quantity + AmountToMakeFullstack);

			//adjust the count to be distributed
			AmountToDistribute -= AmountToMakeFullstack;
			InItem->SetQuantity(AmountToDistribute);

			OnInventoryUpdated.Broadcast();
		}
		else
		{

			ExistingItem->SetQuantity(ExistingItem->Quantity + AmountToDistribute);
			
			OnInventoryUpdated.Broadcast();

			return RequestedAddAmount;
		}
		//check if there is still another valid partial stack of the input item
		ExistingItem = FindNextPartialStack(InItem);
	}

	//no more partial stacks found, check if a new stack can be added
	if (InventoryContents.Num() + 1 <= InventorySlotsCapacity)
	{
		if (AmountToDistribute > 0)
		{
			AddNewItem(InItem->CreateItemCopy(), AmountToDistribute);
			return RequestedAddAmount;
		}
	}
	OnInventoryUpdated.Broadcast();
	return RequestedAddAmount - AmountToDistribute;
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InItem)
{
	if (GetOwner())
	{
		const int32 InitialRequestedAddAmount = InItem->Quantity;

		// handle non stackable
		if (!InItem->NumericData.bIsStackable)
		{
			return HandleNonStackableItems(InItem);
		}

		const int32 StackableAmountAdded = HandleStackableItems(InItem, InitialRequestedAddAmount);

		if (StackableAmountAdded == InitialRequestedAddAmount)
		{
			return FItemAddResult::AddedAll(StackableAmountAdded, FText::Format(
				FText::FromString("Successfully added {0} x{1} to the inventory. Inventory is full!"),
				InItem->TextData.Name,
				StackableAmountAdded
			));
		}
		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			return FItemAddResult::AddedPartial(StackableAmountAdded, FText::Format(
				FText::FromString("Partial amount of  {0} added to the inventory. Amount added = %d."),
				InItem->TextData.Name,
				StackableAmountAdded
			));
		}
		if (StackableAmountAdded <= 0)
		{
			return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("Could not add {0} to the inventory. Inventory is full, or invalid item."),
				InItem->TextData.Name
			));
		}
	}

	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error. GetOwner() check somehow failed"));
}

void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{
	UItemBase* NewItem;
	if (Item->bIsCopy || Item->bIsPickup)
	{
		// if item is already a copy, or is a world pickup
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		//used when splitting or dragging to/from another inventory
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	InventoryContents.Add(NewItem);
	OnInventoryUpdated.Broadcast();
}
