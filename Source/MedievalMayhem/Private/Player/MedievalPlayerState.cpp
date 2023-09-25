// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MedievalPlayerState.h"
#include "AbilitySystem/MedievalAttributeSet.h"
#include "AbilitySystem/MedievalAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

AMedievalPlayerState::AMedievalPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMedievalAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMedievalAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

void AMedievalPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMedievalPlayerState, Level);
}

UAbilitySystemComponent* AMedievalPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMedievalPlayerState::OnRep_Level(int32 OldLevel)
{

}
