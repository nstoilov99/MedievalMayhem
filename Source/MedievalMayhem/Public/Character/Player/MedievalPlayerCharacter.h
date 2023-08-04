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

	virtual void Tick(float DeltaTime) override;
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

	UFUNCTION()
	void ReceiveDamage(class UCharacterAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
	//Movement Input
	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Movement")
	class UInputMappingContext* MedievalMovementMappingContext;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Movement")
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Movement")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Movement")
	class UInputAction* JumpAction;

	//Ability Input
	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Ability")
	class UInputMappingContext* MedievalAbilityMappingContext;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Ability")
	class UInputAction* BasicAbility_Action;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Ability")
	class UInputAction* Ability_1_Action;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Ability")
	class UInputAction* Ability_2_Action;

	UPROPERTY(EditAnywhere, Category = "Medieval|Input|Ability")
	class UInputAction* Ability_3_Action;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	virtual void OnRep_PlayerState() override;

	void InitializeAbilityValues(class AMedievalPlayerState* PS);

};
