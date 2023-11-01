// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MedievalAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UMedievalAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMedievalAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	/*
	* Vital Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, MaxHealth);

	/*
	* Primary Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Intelligence);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vitality, Category = "Primary Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Vitality);	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AllStats, Category = "Primary Attributes")
	FGameplayAttributeData AllStats;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, AllStats);

	/*
	* Secondary Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthPercent, Category = "Secondary Attributes")
	FGameplayAttributeData HealthPercent;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, HealthPercent);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Armor);	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPercent, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPercent;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, ArmorPercent);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dodge, Category = "Secondary Attributes")
	FGameplayAttributeData Dodge;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Dodge);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, MovementSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LifeSteal, Category = "Secondary Attributes")
	FGameplayAttributeData LifeSteal;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, LifeSteal);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealingReceived, Category = "Secondary Attributes")
	FGameplayAttributeData HealingReceived;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, HealingReceived);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthOnKill, Category = "Secondary Attributes")
	FGameplayAttributeData HealthOnKill;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, HealthOnKill);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthOnHit, Category = "Secondary Attributes")
	FGameplayAttributeData HealthOnHit;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, HealthOnHit);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Cooldown, Category = "Secondary Attributes")
	FGameplayAttributeData Cooldown;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, Cooldown);

	/*
	* Resistance Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AllResistance, Category = "Resistance Attributes")
	FGameplayAttributeData AllResistance;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, AllResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, FireResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NatureResistance, Category = "Resistance Attributes")
	FGameplayAttributeData NatureResistance;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, NatureResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FrostResistance, Category = "Resistance Attributes")
	FGameplayAttributeData FrostResistance;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, FrostResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Resistance Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, LightningResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, PhysicalResistance);

	/*
	* Meta Attributes
	*/

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMedievalAttributeSet, IncomingDamage);

	//----------FUNCTIONS----------//
	/*
	* Vital Functions
	*/

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/*
	* Primary Functions
	*/

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Vitality(const FGameplayAttributeData& OldVitality) const;

	UFUNCTION()
	void OnRep_AllStats(const FGameplayAttributeData& OldAllStats) const;

	/*
	* Secondary Functions
	*/

	UFUNCTION()
	void OnRep_HealthPercent(const FGameplayAttributeData& OldHealthPercent) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPercent(const FGameplayAttributeData& OldArmorPercent) const;

	UFUNCTION()
	void OnRep_Dodge(const FGameplayAttributeData& OldDodge) const;

	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;

	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const;

	UFUNCTION()
	void OnRep_HealingReceived(const FGameplayAttributeData& OldHealingReceived) const;

	UFUNCTION()
	void OnRep_HealthOnKill(const FGameplayAttributeData& OldHealthOnKill) const;

	UFUNCTION()
	void OnRep_HealthOnHit(const FGameplayAttributeData& OldHealthOnHit) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_Cooldown(const FGameplayAttributeData& OldCooldown) const;
	
	/*
	* Resistance Functions
	*/

	UFUNCTION()
	void OnRep_AllResistance(const FGameplayAttributeData& OldAllResistance) const;

	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;
	
	UFUNCTION()
	void OnRep_NatureResistance(const FGameplayAttributeData& OldNatureResistance) const;	

	UFUNCTION()
	void OnRep_FrostResistance(const FGameplayAttributeData& OldFrostResistance) const;

	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;

};
