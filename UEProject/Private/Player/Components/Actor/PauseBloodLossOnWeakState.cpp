// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/Actor/PauseBloodLossOnWeakState.h"

#include "Player/Components/Actor/PlayerStats.h"
#include "Player/Components/Actor/WeakState.h"


UPauseBloodLossOnWeakState::UPauseBloodLossOnWeakState()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPauseBloodLossOnWeakState::BeginPlay()
{
	Super::BeginPlay();

	WeakStateComponent = GetOwner()->GetComponentByClass<UWeakState>();
	PlayerStatsComponent = GetOwner()->GetComponentByClass<UPlayerStats>();

	if (!WeakStateComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("PauseBloodLossOnWeakState: No WeakStateComponent found!"));
		return;
	}

	if (!PlayerStatsComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("PauseBloodLossOnWeakState: No PlayerStatsComponent found!"));
		return;
	}

	WeakStateComponent->OnWeakState.AddDynamic(this, &UPauseBloodLossOnWeakState::OnWeakStateChanged);
}

void UPauseBloodLossOnWeakState::OnWeakStateChanged(bool IsWeak)
{
	if (IsWeak)
	{
		CachedBloodLossRate = PlayerStatsComponent->GetBloodLossRate();
		PlayerStatsComponent->SetBloodLossRate(0.0f);
	}
	else
	{
		PlayerStatsComponent->SetBloodLossRate(CachedBloodLossRate);
	}
}
