// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/MedievalUserWidget.h"
#include "InventoryMenuWidget.generated.h"

class AMedievalPlayerCharacter;
/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UInventoryMenuWidget : public UMedievalUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<AMedievalPlayerCharacter> PlayerCharacter;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
