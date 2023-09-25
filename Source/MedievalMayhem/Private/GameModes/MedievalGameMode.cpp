// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MedievalPlayerController.h"
#include "GameModes/MedievalGameMode.h"

void AMedievalGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AMedievalPlayerController* PlayerController = Cast<AMedievalPlayerController>(*It);
		if (PlayerController)
		{
			PlayerController->OnMatchStateSet(MatchState);
		}
	}
}
