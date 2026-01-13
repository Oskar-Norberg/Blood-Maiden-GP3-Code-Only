// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTriggerBase.h"
#include "OneShotDamageTrigger.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UOneShotDamageTrigger : public UDamageTriggerBase
{
	GENERATED_BODY()

public:
	UOneShotDamageTrigger();

protected:
	virtual void OnBeginOverlap(TObjectPtr<UActorComponent> OverlappedComponent) override;
};
