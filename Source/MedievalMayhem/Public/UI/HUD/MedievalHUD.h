// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MedievalHUD.generated.h"

class UMedievalUserWidget;
class UInteractionWidget;
class UInventoryMenuWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
struct FInteractableData;
/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API AMedievalHUD : public AHUD
{
	GENERATED_BODY()
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	bool bIsMenuVisible;

	void DisplayInventory();
	void HideInventory();
	void ToggleInventory();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;
protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY()
	TObjectPtr<UMedievalUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMedievalUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UInventoryMenuWidget> InventoryMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryMenuWidget> InventoryMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

};
