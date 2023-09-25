// Fill out your copyright notice in the Description page of Project Settings.


#include "MedievalAssetManager.h"
#include "MedievalGameplayTags.h"

UMedievalAssetManager& UMedievalAssetManager::Get()
{
	check(GEngine);

	UMedievalAssetManager* MedievalAssetManager = Cast<UMedievalAssetManager>(GEngine->AssetManager);
	return *MedievalAssetManager;
}

void UMedievalAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMedievalGameplayTags::InitializeNativeGameplayTags();
}
