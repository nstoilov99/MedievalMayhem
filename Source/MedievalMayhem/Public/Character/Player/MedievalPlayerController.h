// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MedievalPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API AMedievalPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	void SetHUDHealth(float Health, float MaxHealth);

	void OnMatchStateSet(FName State);
	void HandleMatchHasStarted();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	void PollInit();
private:
	UPROPERTY()
	class AMedievalHUD* MedievalHUD;

	UPROPERTY()
	FName MatchState;

	class UCharacterOverlay* CharacterOverlay;
	bool bInitializeCharacterOverlay = false;

	float HUDHealth;
	float HUDMaxHealth;
};
