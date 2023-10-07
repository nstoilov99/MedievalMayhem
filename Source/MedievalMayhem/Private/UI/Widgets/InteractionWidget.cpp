// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/InteractionWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HoldInteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CurrentInteractionDuration = 0.0f;
}

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
	switch (InteractableData->InteractableType)
	{
	case EInteractableType::EIT_Pickup:
		//HoldInteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		if (InteractableData->Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			QuantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"),
				InteractableData->Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		break;
	case EInteractableType::EIT_Equipment:
		break;
	case EInteractableType::EIT_NonPlayerCharacter:
		break;
	case EInteractableType::EIT_Device:
		break;
	case EInteractableType::EIT_Container:
		break;
	default:
		break;
	}
	ActionText->SetText(InteractableData->Action);
	HoldActionText->SetText(InteractableData->HoldAction);
	NameText->SetText(InteractableData->Name);
}

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.0f;
}