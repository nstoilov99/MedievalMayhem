// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Interaction/InteractionInterface.h"
#include "Weapon.generated.h"

class USphereComponent;
class UWidgetComponent;

UENUM(BlueprintType)
enum class EWeaponState : uint8 
{
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped")
};
UCLASS()
class MEDIEVALMAYHEM_API AWeapon : public AItem, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	/*Interaction Interface Start*/
	void ShowInteractionWidget(bool bShowWidget) override;
	/*Interaction Interface End*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
