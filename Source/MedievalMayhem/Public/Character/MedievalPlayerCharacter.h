// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MedievalCharacterBase.h"
#include "InputActionValue.h"
#include "MedievalPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
/*
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API AMedievalPlayerCharacter : public AMedievalCharacterBase
{
	GENERATED_BODY()

public:
	AMedievalPlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	bool IsWeaponEquipped();
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

private:
	virtual void InitAbilityActorInfo() override;

};
