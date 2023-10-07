// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

class AMedievalPlayerCharacter;

UENUM()
enum class EInteractableType : uint8 
{
	EIT_Pickup UMETA(DisplayName = "Pickup"),
	EIT_Equipment UMETA(DisplayName = "Equipment"),
	EIT_NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
	EIT_Device UMETA(DisplayName = "Device"),
	EIT_Container UMETA(DisplayName = "Container") ,
};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

	FInteractableData() :
	InteractableType(EInteractableType::EIT_Pickup),
	Name(FText::GetEmpty()),
	Action(FText::GetEmpty()),
	Quantity(0),
	InteractionDuration(0.0f)
	{
	};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	UPROPERTY(EditInstanceOnly)
	FText HoldAction;

	UPROPERTY(EditInstanceOnly)
	int8 Quantity;

	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDIEVALMAYHEM_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ShowInteractionWidget(bool bShowWidget) = 0;
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(AMedievalPlayerCharacter* PlayerCharacter);

	FInteractableData InteractableData;
};
