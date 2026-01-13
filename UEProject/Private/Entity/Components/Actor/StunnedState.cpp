// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Components/Actor/StunnedState.h"
#include "Entity/Components/Actor/EntityStats.h"

UStunnedState::UStunnedState()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UStunnedState::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UEntityStats> EntityStats = GetOwner()->GetComponentByClass<UEntityStats>();

	if (!EntityStats)
	{
		UE_LOG(LogTemp, Error, TEXT("UStunnedState::BeginPlay - EntityStats component not found on %s"), *GetOwner()->GetName());
		return;
	}

	EntityStats->OnAttacked.AddDynamic(this, &UStunnedState::EnterStunnedState);
}

void UStunnedState::EnterStunnedState(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser,
	EDamageType DamageType)
{
	if (IsStunned)
	{
		return; // Already in stun-state.
	}
	
	GetWorld()->GetTimerManager().SetTimer(
		StunTimerHandle,
		this,
		&UStunnedState::ExitStunnedState,
		StunDuration,
		false
	);

	IsStunned = true;
	NotifyStunnedState();
}

void UStunnedState::ExitStunnedState()
{
	IsStunned = false;
	NotifyStunnedState();
}

void UStunnedState::NotifyStunnedState()
{
	OnStunned.Broadcast(IsStunned);
}
