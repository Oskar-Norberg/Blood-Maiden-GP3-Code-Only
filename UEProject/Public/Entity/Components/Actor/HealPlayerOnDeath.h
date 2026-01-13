// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealPlayerOnDeath.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UHealPlayerOnDeath : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealPlayerOnDeath();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Healing")
	float HealAmount = 5.0f;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HealPlayer();
};
