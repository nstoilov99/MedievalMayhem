// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HUD/MedievalHUD.h"
#include "Character/HUD/CharacterOverlay.h"
#include "GameFramework/PlayerController.h"

void AMedievalHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMedievalHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AMedievalHUD::AddCharacterOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
		CharacterOverlay->AddToViewport();
	}
}
