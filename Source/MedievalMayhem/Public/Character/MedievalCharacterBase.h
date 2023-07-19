// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MedievalMayhem/MedievalMayhem.h"
#include "GameplayTagContainer.h"
#include "MedievalCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharaterDiedDelegate, AMedievalCharacterBase*, Character);

UCLASS()
class MEDIEVALMAYHEM_API AMedievalCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMedievalCharacterBase(const class FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	UPROPERTY(BlueprintAssignable, Category = "Medieval|Character")
	FCharaterDiedDelegate OnCharacterDied;
	

	UFUNCTION(BlueprintCallable, Category = "Medieval|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Character")
	virtual int32 GetAbilityLevel(MedievalAbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Medieval|Character")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category = "Medieval|Character|Attributes")
	float GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable, Category = "Medieval|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Character|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Character|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "Medieval|Character|Attributes")
	float GetMaxMana() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Medieval|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Medieval|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Medieval|Abilities")
	TArray<TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Medieval|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Medieval|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAtrributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);
};
