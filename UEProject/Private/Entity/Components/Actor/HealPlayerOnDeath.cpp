// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Components/Actor/HealPlayerOnDeath.h"

#include "Entity/Components/Actor/EntityStats.h"


UHealPlayerOnDeath::UHealPlayerOnDeath()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealPlayerOnDeath::BeginPlay()
{
	Super::BeginPlay();

	auto* EntityStats = GetOwner()->FindComponentByClass<UEntityStats>();
	if (!EntityStats)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is null"), *GetName());
		return;
	}

	EntityStats->OnDeath.AddDynamic(this, &UHealPlayerOnDeath::HealPlayer);
}

void UHealPlayerOnDeath::HealPlayer()
{
	// TODO: This will just get the first player controller. Not compatible with any sort of co-op/multiplayer.
	auto* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Player)
	{
		// TODO: i am mentalyl challenged
		UE_LOG(LogTemp, Warning, TEXT("what"));
		return;
	}
	auto* EntityStats = Player->FindComponentByClass<UEntityStats>();
	if (EntityStats)
	{
		EntityStats->Heal(HealAmount, nullptr, GetOwner());
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not get player."));
	}
}
