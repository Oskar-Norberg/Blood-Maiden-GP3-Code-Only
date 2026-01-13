// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Components/Actor/WeakState.h"

#include "Entity/Components/Actor/EntityStats.h"

UWeakState::UWeakState(): IsInWeakState(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeakState::BeginPlay()
{
	Super::BeginPlay();

	EntityStats = GetOwner()->GetComponentByClass<UEntityStats>();
	if (EntityStats)
	{
		EntityStats->OnBloodChanged.AddDynamic(this, &UWeakState::OnBloodChange);
		EntityStats->OnAttacked.AddDynamic(this, &UWeakState::OnAttacked);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UWeakState: No UEntityStats component found on owner actor!"));
	}
}

void UWeakState::OnBloodChange(float NewBloodValue)
{
	bool WeakStateChanged = false;
	
	if (NewBloodValue < WeakStateBloodThreshold)
	{
		if (IsInWeakState)
		{
			return;
		}
		
		IsInWeakState = true;
		JustEnteredWeakState = true;
		WeakStateChanged = true;
	}
	else
	{
		if (IsInWeakState && NewBloodValue >= WeakStateBloodThreshold)
		{
			IsInWeakState = false;
			WeakStateChanged = true;
			JustEnteredWeakState = false;
		}
		
	}

	if (WeakStateChanged)
	{
		OnWeakState.Broadcast(IsInWeakState);
	}
}

void UWeakState::OnAttacked(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser,
	EDamageType DamageType)
{
	if (JustEnteredWeakState)
	{
		JustEnteredWeakState = false;
		return;
	}
	
	// If you take any damage in weak state. Die.
	if (IsInWeakState)
	{
		if (EntityStats)
		{
			EntityStats->Kill(nullptr, this->GetOwner());
		}
	}
}
