// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityStats.h"
#include "Components/ActorComponent.h"
#include "KnockbackOnDamaged.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKnockback);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UKnockbackOnDamaged : public UActorComponent
{
	GENERATED_BODY()

public:
	UKnockbackOnDamaged();

public:
	UPROPERTY(BlueprintAssignable)
	FOnKnockback OnKnockback;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float KnockbackStrength = 1000.0f;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnDamaged(float DamageAmount,
	AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType);

	void NotifyKnockback() const;
};
