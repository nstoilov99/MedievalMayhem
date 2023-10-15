// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MedievalPlayerController.generated.h"

class AMedievalPlayerCharacter;
class UInputMappingContext;
class UInputAction;
class UMedievalInputConfig;
class AMedievalHUD;
class IInteractionInterface;
struct FInputActionValue;
struct FGameplayTag;
/**
 * 
 */
UCLASS(BlueprintType)
class MEDIEVALMAYHEM_API AMedievalPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMedievalPlayerController();

	virtual void Tick(float DeltaTime) override;
	void OnMatchStateSet(FName State);
	void UpdateInteractionWidget() const;
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }
	FORCEINLINE void AddToActorsToIgnore(AActor* Actor) { TraceActorsToIgnore.Add(Actor); }
	FORCEINLINE void RemoveFromActorToIgnore(AActor* Actor) { TraceActorsToIgnore.Remove(Actor); }
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();

	void ToggleMenu();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UFUNCTION(Client, Reliable)
	void TraceInteractable();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void Interact();
	void EndInteract();
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MedievalContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMedievalInputConfig> AbilityInputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceScale = 700;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceSphereRadius = 15.f;

	UPROPERTY(EditAnywhere, Category = "Trace")
	float InteractionCheckFrequency = 0.1f;

	UPROPERTY()
	TObjectPtr<AMedievalHUD> HUD;

	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractable = nullptr;

	UPROPERTY()
	float LastInteractionCheckTime = 0.f;

	UPROPERTY()
	bool bIsInteracting = false;

	UPROPERTY()
	TScriptInterface<IInteractionInterface> TargetInteractable;

	FTimerHandle TimerHandle_Interaction;
	TArray<AActor*> TraceActorsToIgnore;
	TObjectPtr<AMedievalPlayerCharacter> OwningCharacter;
};
