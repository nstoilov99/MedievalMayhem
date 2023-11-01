// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MedievalAttributeSet.h"
#include "Net/UnrealNetwork.h"

UMedievalAttributeSet::UMedievalAttributeSet()
{
}

void UMedievalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, HealthPercent, COND_None, REPNOTIFY_Always);
	//Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, AllStats, COND_None, REPNOTIFY_Always);
	//Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, ArmorPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Dodge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, HealingReceived, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, HealthOnHit, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, HealthOnKill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Cooldown, COND_None, REPNOTIFY_Always);
	//Resistance Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, AllResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, NatureResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, FrostResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
}

void UMedievalAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Health, OldHealth);
}

void UMedievalAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, MaxHealth, OldMaxHealth);
}

void UMedievalAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Strength, OldStrength);
}

void UMedievalAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Dexterity, OldDexterity);
}

void UMedievalAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Intelligence, OldIntelligence);
}

void UMedievalAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Vitality, OldVitality);
}

void UMedievalAttributeSet::OnRep_AllStats(const FGameplayAttributeData& OldAllStats) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, AllStats, OldAllStats);
}

void UMedievalAttributeSet::OnRep_HealthPercent(const FGameplayAttributeData& OldHealthPercent) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, HealthPercent	, OldHealthPercent);
}

void UMedievalAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Armor, OldArmor);
}

void UMedievalAttributeSet::OnRep_ArmorPercent(const FGameplayAttributeData& OldArmorPercent) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, ArmorPercent, OldArmorPercent);
}

void UMedievalAttributeSet::OnRep_Dodge(const FGameplayAttributeData& OldDodge) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Dodge, OldDodge);
}

void UMedievalAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UMedievalAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UMedievalAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UMedievalAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UMedievalAttributeSet::OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, LifeSteal, OldLifeSteal);
}

void UMedievalAttributeSet::OnRep_HealingReceived(const FGameplayAttributeData& OldHealingReceived) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, HealingReceived, OldHealingReceived);
}

void UMedievalAttributeSet::OnRep_HealthOnKill(const FGameplayAttributeData& OldHealthOnKill) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, HealthOnKill, OldHealthOnKill);
}

void UMedievalAttributeSet::OnRep_HealthOnHit(const FGameplayAttributeData& OldHealthOnHit) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, HealthOnHit, OldHealthOnHit);
}

void UMedievalAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UMedievalAttributeSet::OnRep_Cooldown(const FGameplayAttributeData& OldCooldown) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Cooldown, OldCooldown);
}

void UMedievalAttributeSet::OnRep_AllResistance(const FGameplayAttributeData& OldAllResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, AllResistance, OldAllResistance);
}

void UMedievalAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, FireResistance, OldFireResistance);
}

void UMedievalAttributeSet::OnRep_NatureResistance(const FGameplayAttributeData& OldNatureResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, NatureResistance, OldNatureResistance);
}

void UMedievalAttributeSet::OnRep_FrostResistance(const FGameplayAttributeData& OldFrostResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, FrostResistance, OldFrostResistance);
}

void UMedievalAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, LightningResistance, OldLightningResistance);
}

void UMedievalAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, PhysicalResistance, OldPhysicalResistance);
}
