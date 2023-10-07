// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Pickup.generated.h"

class UDataTable;
class UItemBase;

UCLASS()
class MEDIEVALMAYHEM_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	void InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);
	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	/* Interaction Interface Begin */
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	/* Interaction Interface End */

	FORCEINLINE UItemBase* GetItemData() { return ItemReference; }
protected:

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	TObjectPtr<UStaticMeshComponent> PickupMesh;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	FName DesiredItemID;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	int32 ItemQuantity;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
	TObjectPtr<UItemBase> ItemReference;

	UPROPERTY(VisibleInstanceOnly, Category = "Pickup | Interaction")
	FInteractableData InstanceInteractableData;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Interaction Interface Begin */
	virtual void ShowInteractionWidget(bool bShowWidget) override; 
	virtual void Interact(AMedievalPlayerCharacter* PlayerCharacter) override;
	/* Interaction Interface End */
	void UpdateInteractableData();
	void TakePickup(const AMedievalPlayerCharacter* Taker);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
