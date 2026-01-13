// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Components/Actor/DestroyActorOnDeath.h"
#include "Entity/Components/Actor/EntityStats.h"


UDestroyActorOnDeath::UDestroyActorOnDeath()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDestroyActorOnDeath::BeginPlay()
{
	Super::BeginPlay();

	auto* EntityStats = GetOwner()->FindComponentByClass<UEntityStats>();
	if (!EntityStats)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is null"), *GetName());
		return;
	}

	EntityStats->OnDeath.AddDynamic(this, &UDestroyActorOnDeath::StartDestroyTimer);
}

void UDestroyActorOnDeath::StartDestroyTimer()
{
	// Delay the destruction to allow any other death events to finish first.
	GetWorld()->GetTimerManager().SetTimer(
		DestroyActorHandle,
		this,
		&UDestroyActorOnDeath::EndDestroyTimer,
		DelayBeforeDestroy,
		false
		);
}

void UDestroyActorOnDeath::EndDestroyTimer()
{
	if (!GetOwner())
	{
		// Actor has already been destroyed.
		return;
	}
	if (GetOwner()->IsPendingKillPending())
	{
		// Actor is already pending kill, no need to destroy again.
		return;
	}
	
	GetOwner()->Destroy();
}
