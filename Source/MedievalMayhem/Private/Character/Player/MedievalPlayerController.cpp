// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/MedievalPlayerController.h"
#include "Character/Player/MedievalPlayerState.h"
#include "AbilitySystemComponent.h"

void AMedievalPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AMedievalPlayerState* PS = GetPlayerState<AMedievalPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}