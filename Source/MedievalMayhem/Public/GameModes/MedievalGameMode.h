// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MedievalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API AMedievalGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	virtual void OnMatchStateSet() override;
};
