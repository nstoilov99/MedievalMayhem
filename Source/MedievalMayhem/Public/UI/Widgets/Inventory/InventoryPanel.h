// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanel.generated.h"

class AMedievalPlayerCharacter;
class UInventoryComponent;
class UInventoryItemSlot;
class UTextBlock;
class UWrapBox;
/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> InventoryWrapBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CapacityInfo;

	UPROPERTY()
	TObjectPtr<AMedievalPlayerCharacter> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryItemSlot> InventorySlotClass;
	
	UFUNCTION()
	void RefreshInventory();
protected:

	void SetInfoText();
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
