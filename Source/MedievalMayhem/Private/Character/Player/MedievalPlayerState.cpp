// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/MedievalPlayerState.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"

AMedievalPlayerState::AMedievalPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.f;
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void AMedievalPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &AMedievalPlayerState::CharacterLevelChanged);
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AMedievalPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AMedievalPlayerState::MaxHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this, &AMedievalPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &AMedievalPlayerState::MaxManaChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AMedievalPlayerState::StunTagChanged);
	}
}

UAbilitySystemComponent* AMedievalPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* AMedievalPlayerState::GetAttrubuteSetBase() const
{
	return AttributeSetBase;
}

bool AMedievalPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void AMedievalPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//TO DO HUD later...
}

int32 AMedievalPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

float AMedievalPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float AMedievalPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float AMedievalPlayerState::GetMana() const
{
	return AttributeSetBase->GetMana();
}

float AMedievalPlayerState::GetMaxMana() const
{
	return AttributeSetBase->GetMaxMana();
}

void AMedievalPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed!"))
}

void AMedievalPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed!"))
}

void AMedievalPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Mana Changed!"))
}

void AMedievalPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Mana Changed!"))
}

void AMedievalPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Level Changed!"))
}

void AMedievalPlayerState::StunTagChanged(const FGameplayTag Callback, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
