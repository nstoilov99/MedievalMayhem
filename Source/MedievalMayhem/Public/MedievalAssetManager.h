// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MedievalAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UMedievalAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UMedievalAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
