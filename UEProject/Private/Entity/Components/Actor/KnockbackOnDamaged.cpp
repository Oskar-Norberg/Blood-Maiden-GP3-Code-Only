// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Components/Actor/KnockbackOnDamaged.h"

#include "Entity/Components/Actor/EntityStats.h"


UKnockbackOnDamaged::UKnockbackOnDamaged()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKnockbackOnDamaged::BeginPlay()
{
	Super::BeginPlay();

	auto* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	auto* EntityStats = Owner->GetComponentByClass<UEntityStats>();
	if (!EntityStats)
	{
		return;
	}

	EntityStats->OnAttacked.AddDynamic(this, &UKnockbackOnDamaged::OnDamaged);
	
}

void UKnockbackOnDamaged::OnDamaged(float DamageAmount,
	AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType)
{
	if (!DamageCauser)
	{
		return;
	}
	if (!GetOwner())
	{
		return;
	}
	
	auto* Owner = GetOwner();

	const FVector DirectionToDamageCauser = (DamageCauser->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal();
	const FVector KnockbackImpulse = DirectionToDamageCauser * KnockbackStrength;

	if (auto* RootComp = Cast<UPrimitiveComponent>(Owner->GetRootComponent()))
	{
		RootComp->AddImpulse(KnockbackImpulse);
		NotifyKnockback();
	}
}

void UKnockbackOnDamaged::NotifyKnockback() const
{
	OnKnockback.Broadcast();
}
