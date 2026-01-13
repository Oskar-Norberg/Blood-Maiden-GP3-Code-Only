// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityStats.h"
#include "Components/ActorComponent.h"
#include "GlobalEntityDamageEventSender.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UGlobalEntityDamageEventSender : public UActorComponent
{
	GENERATED_BODY()

public:
	UGlobalEntityDamageEventSender();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnAttacked(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType);
};
