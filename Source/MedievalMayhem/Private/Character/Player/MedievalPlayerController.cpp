// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/MedievalPlayerCharacter.h"
#include "Character/Player/MedievalPlayerController.h"
#include "Character/Player/MedievalPlayerState.h"
#include "Character/HUD/CharacterOverlay.h"
#include "Character/HUD/MedievalHUD.h"
#include "GameModes/MedievalGameMode.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AbilitySystemComponent.h"

void AMedievalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MedievalHUD = Cast<AMedievalHUD>(GetHUD());
}

void AMedievalPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PollInit();
}

void AMedievalPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AMedievalPlayerState* PS = GetPlayerState<AMedievalPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}

	AMedievalPlayerCharacter* MedievalCharacter = Cast<AMedievalPlayerCharacter>(InPawn);
	if (MedievalCharacter)
	{	
		SetHUDHealth(MedievalCharacter->GetHealth(), MedievalCharacter->GetMaxHealth());
	}
}

void AMedievalPlayerController::PollInit()
{
	if (CharacterOverlay == nullptr)
	{
		if (MedievalHUD && MedievalHUD->CharacterOverlay)
		{
			CharacterOverlay = MedievalHUD->CharacterOverlay;
			if (CharacterOverlay)
			{
				SetHUDHealth(HUDHealth, HUDMaxHealth);
			}
		}
	}
}

void AMedievalPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	MedievalHUD = MedievalHUD == nullptr ? Cast<AMedievalHUD>(GetHUD()) : MedievalHUD;

	bool bHUDValid = MedievalHUD &&
		MedievalHUD->CharacterOverlay &&
		MedievalHUD->CharacterOverlay->HealthBar &&
		MedievalHUD->CharacterOverlay->HealthText;

	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		MedievalHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		MedievalHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
	else
	{
		bInitializeCharacterOverlay = true;
		HUDHealth = Health;
		HUDMaxHealth = MaxHealth;
	}
}

void AMedievalPlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;
	if (MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
}

void AMedievalPlayerController::HandleMatchHasStarted()
{
	MedievalHUD = MedievalHUD == nullptr ? Cast<AMedievalHUD>(GetHUD()) : MedievalHUD;
	if (MedievalHUD)
	{
		if (MedievalHUD->CharacterOverlay == nullptr)
		{
			MedievalHUD->AddCharacterOverlay();
		}
	}
}
