// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MedievalGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UMedievalGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
};
