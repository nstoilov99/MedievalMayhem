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
	//Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	//Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Dodge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedievalAttributeSet, Cooldown, COND_None, REPNOTIFY_Always);
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

void UMedievalAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Armor, OldArmor);
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

void UMedievalAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UMedievalAttributeSet::OnRep_Cooldown(const FGameplayAttributeData& OldCooldown) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedievalAttributeSet, Cooldown, OldCooldown);
}
