// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OnDamageEvent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UEPROJECT_API UOnDamageEvent : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Entity Damage Data")
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Entity Damage Data")
	TObjectPtr<AActor> DamagedActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Entity Damage Data")
	TObjectPtr<AActor> DamagedByActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Entity Damage Data")
	TObjectPtr<AController> DamageInstigator;
};
