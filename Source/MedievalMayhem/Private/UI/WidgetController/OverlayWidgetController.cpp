// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/MedievalAbilitySystemComponent.h"
#include "AbilitySystem/MedievalAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMedievalAttributeSet* MedievalAttributeSet = CastChecked<UMedievalAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(MedievalAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MedievalAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{

	const UMedievalAttributeSet* MedievalAttributeSet = CastChecked<UMedievalAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MedievalAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MedievalAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) 
			 {
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
	);
}
