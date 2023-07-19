// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "MedievalPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API AMedievalPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AMedievalPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent()const override;

	class UCharacterAttributeSetBase* GetAttrubuteSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|PlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|PlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "Medieval|Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Attributes")
	float GetMaxMana() const;

protected:
	UPROPERTY()
	class UCharacterAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	UCharacterAttributeSetBase* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle ManaChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;
	FDelegateHandle CharacterLevelChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag Callback, int32 NewCount);
};
