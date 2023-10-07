// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MedievalHUD.h"
#include "UI/Widgets/MedievalUserWidget.h"
#include "UI/Widgets/InteractionWidget.h"
#include "UI/Widgets/Inventory/InventoryMenuWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AMedievalHUD::BeginPlay()
{
	Super::BeginPlay();
	if (InventoryMenuWidgetClass)
	{
		InventoryMenuWidget = CreateWidget<UInventoryMenuWidget>(GetWorld(), InventoryMenuWidgetClass);
		InventoryMenuWidget->AddToViewport(5);
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsMenuVisible = false;
	}
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

UOverlayWidgetController* AMedievalHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AMedievalHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitialized, please fill out BP_MedievalHud"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unitialized, please fill out BP_MedievalHud"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UMedievalUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WigetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WigetController);

	WigetController->BroadcastInitialValues();

	Widget->AddToViewport();
}

void AMedievalHUD::DisplayInventory()
{
	if (InventoryMenuWidget)
	{
		bIsMenuVisible = true;
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMedievalHUD::HideInventory()
{
	if (InventoryMenuWidget)
	{
		bIsMenuVisible = false;
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMedievalHUD::ToggleInventory()
{
	if (bIsMenuVisible)
	{
		HideInventory();
		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayInventory();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void AMedievalHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMedievalHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMedievalHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}

