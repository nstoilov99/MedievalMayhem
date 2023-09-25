// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MedievalCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MedievalAttributeSet.h"
#include "AbilitySystem/MedievalAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

AMedievalCharacterBase::AMedievalCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	bAlwaysRelevant = true;
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemovedOnDeath"));

}

// Called when the game starts or when spawned
void AMedievalCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMedievalCharacterBase::InitAbilityActorInfo()
{
}

void AMedievalCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AMedievalCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1);
	ApplyEffectToSelf(DefaultVitalAttributes, 1);
}

void AMedievalCharacterBase::AddCharacterAbilities()
{
	UMedievalAbilitySystemComponent* MedievalASC = CastChecked<UMedievalAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	MedievalASC->AddCharacterAbilities(StartupAbilities);
}

UAbilitySystemComponent* AMedievalCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool AMedievalCharacterBase::IsWeaponEquipped()
{
	return false;
}

USkeletalMeshComponent* AMedievalCharacterBase::GetWeapon()
{
	return nullptr;
}
