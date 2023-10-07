// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Interfaces/InteractionInterface.h"
#include "Equipment.generated.h"

class USphereComponent;
class UWidgetComponent;
class AMedievalPlayerCharacter;


UCLASS()
class MEDIEVALMAYHEM_API AEquipment: public AItem, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipment();

	void SetWeaponState(EWeaponState State);
	/*Interaction Interface Start*/
	void ShowInteractionWidget(bool bShowWidget) override;
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(AMedievalPlayerCharacter* PlayerCharacter) override;
	/*Interaction Interface End*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Test")
	FInteractableData InstanceInteractableData;
	UPROPERTY(EditAnywhere)
	EWeaponState WeaponState;
};
