// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MedievalCharacterBase.h"
#include "InputActionValue.h"
#include "MedievalPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API AMedievalPlayerCharacter : public AMedievalCharacterBase
{
	GENERATED_BODY()

public:
	AMedievalPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	class USpringArmComponent* GetCameraBoom();

	class UCameraComponent* GetFollowCamera();

	UFUNCTION(BlueprintCallable, Category = "Medieval|Camera")
	float GetStartingCameraBoomArmLength();

	UFUNCTION(BlueprintCallable, Category = "Medieval|Camera")
	FVector GetStartingCameraBoomLocation();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Medieval|Camera")
	float BaseTurnRate = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Medieval|Camera")
	float BaseLookUpRate = 45.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Medieval|Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly, Category = "Medieval|Camera")
	FVector StartingCameraBoomLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Medieval|Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Medieval|Camera")
	class UCameraComponent* FollowCamera;

	bool bASCInputBound = false;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input")
	class UInputMappingContext* MedievalMappingContext;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input")
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input")
	class UInputAction* JumpAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void LookUp(float Value);

	void LookUpRate(float Value);

	void Turn(float Value);

	void TurnRate(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	virtual void OnRep_PlayerState() override;

	void InitializeAbilityValues(class AMedievalPlayerState* PS);

	void BindASCInput();

};
