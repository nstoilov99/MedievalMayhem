// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MedievalCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Character/Abilities/CharacterGameplayAbility.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

AMedievalCharacterBase::AMedievalCharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	bAlwaysRelevant = true;
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemovedOnDeath"));
}

// Called when the game starts or when spawned
void AMedievalCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMedievalCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMedievalCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AMedievalCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}


bool AMedievalCharacterBase::IsAlive() const
{
	float Health = GetHealth();
	return Health > 0.0f;
}

int32 AMedievalCharacterBase::GetAbilityLevel(MedievalAbilityID AbilityID) const
{
	return 1;
}

void AMedievalCharacterBase::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilitiesGiven) return;
	for (TSubclassOf<UCharacterGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		UE_LOG(LogTemp, Warning, TEXT("Ability Name : %s"), *StartupAbility.GetDefaultObject()->GetName())
	}
}

void AMedievalCharacterBase::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->bCharacterAbilitiesGiven) return;

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities()) 
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = false;
}

void AMedievalCharacterBase::InitializeAtrributes()
{
	if (!AbilitySystemComponent.IsValid()) return;

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in Character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContextHandle);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void AMedievalCharacterBase::AddStartupEffects()
{
	bool bHasAuth = GetLocalRole() != ROLE_Authority;
	bool bAbilityCompValid = !AbilitySystemComponent.IsValid();
	bool bEffectsApp = !AbilitySystemComponent->bStartupEffectsApplied;
	bool HasValidAuth = bHasAuth || bAbilityCompValid || bEffectsApp;

	UE_LOG(LogTemp, Warning, TEXT("bHasAuth value is %s"), (bHasAuth ? TEXT("true") : TEXT("false")));
	UE_LOG(LogTemp, Warning, TEXT("bAbilityCompValid value is %s"), (bAbilityCompValid ? TEXT("true") : TEXT("false")));
	UE_LOG(LogTemp, Warning, TEXT("bEffectsApp value is %s"), (bEffectsApp ? TEXT("true") : TEXT("false")));
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContextHandle);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void AMedievalCharacterBase::Die()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->Velocity = FVector().ZeroVector;

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
}

void AMedievalCharacterBase::FinishDying()
{
	Destroy();
}
float AMedievalCharacterBase::GetCharacterLevel() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetLevel();
	}

	return 0.0f;
}

float AMedievalCharacterBase::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

void AMedievalCharacterBase::SetHealth(float Health)
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->SetHealth(Health);
	}
}

float AMedievalCharacterBase::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

float AMedievalCharacterBase::GetMana() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMana();
	}

	return 0.0f;
}

void AMedievalCharacterBase::SetMana(float Mana)
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->SetMana(Mana);
	}
}

float AMedievalCharacterBase::GetMaxMana() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxMana();
	}

	return 0.0f;
}