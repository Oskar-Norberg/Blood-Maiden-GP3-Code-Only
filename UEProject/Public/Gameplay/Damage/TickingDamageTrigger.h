// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTriggerBase.h"
#include "TickingDamageTrigger.generated.h"

class UEntityStats;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UTickingDamageTrigger : public UDamageTriggerBase
{
	GENERATED_BODY()

public:
	UTickingDamageTrigger();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
						   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void OnBeginOverlap(TObjectPtr<UActorComponent> OverlappedComponent) override;
	virtual void OnEndOverlap(TObjectPtr<UActorComponent> OverlappedComponent) override;

private:
	UPROPERTY()
	TSet<TObjectPtr<UEntityStats>> OverlappedComponents;
};
