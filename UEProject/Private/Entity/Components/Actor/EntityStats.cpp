// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Components/Actor/EntityStats.h"

#include "ComponentUtils.h"

UEntityStats::UEntityStats()
{
	PrimaryComponentTick.bCanEverTick = true;
	CanTakeDamage = true;
}

void UEntityStats::BeginPlay()
{
	Super::BeginPlay();
	
	// TODO: Mayhaps this will fuck up the save system.
	SetBlood(StartingBlood);
	GetOwnerHierarchy();
}
void UEntityStats::GetOwnerHierarchy()
{
	AActor* Owner = GetOwner();
	bool HaveParent = true;
	while (HaveParent)
	{
		AActor* ParentOwner = Owner->GetAttachParentActor();
		if (IsValid(ParentOwner))
		{
			Owner = ParentOwner;
		}
		else
		{
			OwnerActor = Owner;
			HaveParent = false;
		}
	}
}

void UEntityStats::Attack(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType)
{
	if (!CanTakeDamage || IsDead)
	{
		return;
	}
	if (DamageCauser != nullptr)
	{
		if(DamageCauser->ActorHasTag("Enemy") && OwnerActor->ActorHasTag("Enemy")) return;
	}
	SetBlood(CurrentBlood - DamageAmount);
	NotifyAttacked(DamageAmount, DamageInstigator, DamageCauser, DamageType);
}

void UEntityStats::Heal(float HealAmount, AController* HealInstigator, AActor* HealCauser)
{
	SetBlood(CurrentBlood + HealAmount);
	NotifyHealed(HealAmount, HealInstigator, HealCauser);
}

void UEntityStats::Kill(AController* DamageInstigator, AActor* DamageCauser)
{
	CurrentBlood = MinBlood;
	ClampBlood();
	NotifyDeath();
}

void UEntityStats::AddBlood(float Amount)
{
	SetBlood(CurrentBlood + Amount);
}

void UEntityStats::RemoveBlood(float Amount)
{
	SetBlood(CurrentBlood - Amount);
}

void UEntityStats::SetBlood(float Amount)
{
	CurrentBlood = Amount;
	
	ClampBlood();
	NotifyBloodChanged();

	if (CurrentBlood <= MinBlood) //I made it so it calls the NotifyDeath() after the death animation for the enemy is done, do the same for the player
	{
		NotifyDeath();
	}
}

void UEntityStats::AddMaxBlood(int Amount)
{
	SetMaxBlood(MaxBlood + Amount);
}

void UEntityStats::RemoveMaxBlood(int Amount)
{
	SetMaxBlood(MaxBlood - Amount);
}

void UEntityStats::SetMaxBlood(int NewMaxBlood)
{
	MaxBlood = NewMaxBlood;
	NotifyBloodBoundsChanged();
}

void UEntityStats::AddMinBlood(int Amount)
{
	SetMinBlood(MinBlood + Amount);
}

void UEntityStats::RemoveMinBlood(int Amount)
{
	SetMinBlood(MinBlood - Amount);
}

void UEntityStats::SetMinBlood(int NewMinBlood)
{
	MinBlood = NewMinBlood;
	NotifyBloodBoundsChanged();
}

float UEntityStats::GetCurrentBlood() const
{
	return CurrentBlood;
}

int UEntityStats::GetMinBlood() const
{
	return MinBlood;
}

void UEntityStats::SetCanTakeDamage(bool NewCanTakeDamage)
{
	CanTakeDamage = NewCanTakeDamage;
	OnCanTakeDamageChanged.Broadcast(NewCanTakeDamage);
}

int UEntityStats::GetMaxBlood() const
{
	return MaxBlood;
}

void UEntityStats::ClampBlood()
{
	CurrentBlood = FMath::Clamp(CurrentBlood, MinBlood, MaxBlood);
}

void UEntityStats::NotifyAttacked(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType) const
{
	OnAttacked.Broadcast(DamageAmount, DamageInstigator, DamageCauser, DamageType);
}

void UEntityStats::NotifyHealed(float HealAmount, AController* HealInstigator, AActor* HealCauser) const
{
	OnHealed.Broadcast(HealAmount, HealInstigator, HealCauser);
}

void UEntityStats::NotifyDeath()
{
	if (IsDead)
	{
		return;
	}
	
	IsDead = true;
	OnDeath.Broadcast();
}

void UEntityStats::NotifyBloodChanged() const
{
	OnBloodChanged.Broadcast(CurrentBlood);
}

void UEntityStats::NotifyBloodBoundsChanged() const
{
	OnBloodBoundsChanged.Broadcast(MinBlood, MaxBlood);
}
