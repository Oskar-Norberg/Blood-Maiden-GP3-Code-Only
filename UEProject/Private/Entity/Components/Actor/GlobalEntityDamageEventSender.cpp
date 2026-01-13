// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Components/Actor/GlobalEntityDamageEventSender.h"
#include "Entity/Components/Actor/EntityStats.h"
#include "Events/Damage/OnDamageEvent.h"
#include "Subsystems/World/EventBusSubsystem.h"
#include "Systems/Eventbus/Listener/Interface/EventBusInterface.h"


UGlobalEntityDamageEventSender::UGlobalEntityDamageEventSender()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGlobalEntityDamageEventSender::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UEntityStats> EntityStats = GetOwner()->GetComponentByClass<UEntityStats>();

	if (EntityStats)
	{
		EntityStats.Get()->OnAttacked.AddDynamic(this, &UGlobalEntityDamageEventSender::OnAttacked);
	}
}

void UGlobalEntityDamageEventSender::OnAttacked(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType)
{
	TScriptInterface<IEventBusInterface> EventBus = GetWorld()->GetSubsystem<UEventBusSubsystem>();

	if (!EventBus)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEntityDamageEventSender::OnAttacked - EventBus is null!"));
		return;
	}

	TObjectPtr<UOnDamageEvent> DamageEvent = NewObject<UOnDamageEvent>();
	DamageEvent->DamageAmount = DamageAmount;
	DamageEvent->DamagedActor = GetOwner();
	DamageEvent->DamagedByActor = DamageCauser;
	DamageEvent->DamageInstigator = DamageInstigator;

	EventBus->Publish(DamageEvent, UOnDamageEvent::StaticClass());
}

