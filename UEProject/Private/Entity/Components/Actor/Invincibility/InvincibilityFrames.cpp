// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Components/Actor/Invincibility/InvincibilityFrames.h"
#include "Entity/Components/Actor/EntityStats.h"

void UInvincibilityFrames::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	auto& WorldTimerManager = GetOwner()->GetWorldTimerManager();
	
	if (WorldTimerManager.IsTimerActive(InvincibilityTimerHandle))
	{
		return;
	}

	InteractorStats = Cast<AActor>(Interactor.GetObject())->GetComponentByClass<UEntityStats>();
	if (!InteractorStats)
	{
		UE_LOG(LogTemp, Error, TEXT("InvincibilityFrames: No StatsComponent found!"));
	}

	InteractorStats->SetCanTakeDamage(false);
	NotifyInvincibilityChanged();
	
	WorldTimerManager.SetTimer(
		InvincibilityTimerHandle,
		this,
		&UInvincibilityFrames::EndInvincibility,
		InvincibilityDuration,
		false
		);
}

void UInvincibilityFrames::EndInvincibility()
{
	if (!InteractorStats)
	{
		UE_LOG(LogTemp, Error, TEXT("InvincibilityFrames: No StatsComponent found!"));
	}

	InteractorStats->SetCanTakeDamage(true);
	NotifyInvincibilityChanged();
}

void UInvincibilityFrames::NotifyInvincibilityChanged() const
{
	OnInvincibilityChanged.Broadcast(!InteractorStats->GetCanTakeDamage());
}
