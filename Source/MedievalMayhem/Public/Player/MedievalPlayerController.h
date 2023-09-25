// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MedievalPlayerController.generated.h"


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
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void Interact();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void TracePlayerInteractable();
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

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMedievalInputConfig> AbilityInputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceScale = 700;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceSphereRadius = 15.f;

	IInteractionInterface* LastInteraction;
};
