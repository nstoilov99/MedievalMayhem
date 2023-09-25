// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MedievalHUD.h"
#include "UI/Widget/MedievalUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

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
	checkf(OverlayWidgetClass, TEXT("Overlay Widet Class unitialized, please fill out BP_MedievalHud"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widet Controller Class unitialized, please fill out BP_MedievalHud"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UMedievalUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WigetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WigetController);

	WigetController->BroadcastInitialValues();

	Widget->AddToViewport();
}
