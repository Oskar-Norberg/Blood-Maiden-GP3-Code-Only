// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Damage/OneShotDamageTrigger.h"

#include "Entity/Components/Actor/EntityStats.h"

UOneShotDamageTrigger::UOneShotDamageTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOneShotDamageTrigger::OnBeginOverlap(TObjectPtr<UActorComponent> OverlappedComponent)
{
	Super::OnBeginOverlap(OverlappedComponent);

	auto* HealthComponent = Cast<UEntityStats>(OverlappedComponent);
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stats component == null???"))
		return;
	}
	
	HealthComponent->RemoveBlood(Damage);
}