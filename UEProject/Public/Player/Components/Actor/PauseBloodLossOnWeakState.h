// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PauseBloodLossOnWeakState.generated.h"


class UPlayerStats;
class UWeakState;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UPauseBloodLossOnWeakState : public UActorComponent
{
	GENERATED_BODY()

public:
	UPauseBloodLossOnWeakState();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UWeakState> WeakStateComponent;
	UPROPERTY()
	TObjectPtr<UPlayerStats> PlayerStatsComponent;

	float CachedBloodLossRate;
	
	UFUNCTION()
	void OnWeakStateChanged(bool IsWeak);
};
