// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Entity/Components/Actor/EntityStats.h"
#include "PlayerStats.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class UEPROJECT_API UPlayerStats : public UEntityStats
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

public:
	float GetBloodLossRate() const { return BloodLossRatePerSeconds; }
	void SetBloodLossRate(float NewBloodLossRate) { BloodLossRatePerSeconds = NewBloodLossRate; }

protected:
	virtual void BeginPlay() override;

	//No unit for units/seconds. Slightly ugly.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats/Properties")
	float BloodLossRatePerSeconds;
};


