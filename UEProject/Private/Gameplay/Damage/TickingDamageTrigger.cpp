// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Damage/TickingDamageTrigger.h"
#include "Entity/Components/Actor/EntityStats.h"

UTickingDamageTrigger::UTickingDamageTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTickingDamageTrigger::OnBeginOverlap(TObjectPtr<UActorComponent> OverlappedComponent)
{
	Super::OnBeginOverlap(OverlappedComponent);
	
	auto* HealthComponent = Cast<UEntityStats>(OverlappedComponent);

	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stats component == null???"))
		return;
	}

	// Initial damage.
	HealthComponent->RemoveBlood(Damage);
	OverlappedComponents.Add(HealthComponent);
}

void UTickingDamageTrigger::OnEndOverlap(TObjectPtr<UActorComponent> OverlappedComponent)
{
	Super::OnEndOverlap(OverlappedComponent);
	
	auto* HealthComponent = Cast<UEntityStats>(OverlappedComponent);
	
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stats component == null???"))
		return;
	}

	OverlappedComponents.Remove(HealthComponent);
}

void UTickingDamageTrigger::TickComponent(float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
	for (auto Component : OverlappedComponents)
	{
		if (!Component)
		{
			continue;
		}
		
		Component->RemoveBlood(Damage);
	}
}

