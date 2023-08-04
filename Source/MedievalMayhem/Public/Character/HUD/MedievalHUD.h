// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MedievalHUD.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API AMedievalHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Player|Stats")
	TSubclassOf<class UUserWidget> CharacterOverlayClass;

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;

	void AddCharacterOverlay();
protected:
	virtual void BeginPlay() override;
};
