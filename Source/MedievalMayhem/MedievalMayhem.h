// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class MedievalAbilityID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
	Ability1 UMETA(DisplayName = "BasicAbility"),
	Ability2 UMETA(DisplayName = "Ability2"),
	Ability3 UMETA(DisplayName = "Ability3"),
	Ability4 UMETA(DisplayName = "Ability4"),
	Ability5 UMETA(DisplayName = "Ability5"),
};