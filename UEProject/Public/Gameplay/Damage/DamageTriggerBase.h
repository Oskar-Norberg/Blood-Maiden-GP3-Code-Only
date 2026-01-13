// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Utilities/Trigger/ClassOverlapComponent.h"
#include "DamageTriggerBase.generated.h"

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UDamageTriggerBase : public UClassOverlapComponent
{
	GENERATED_BODY()

public:
	UDamageTriggerBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger Properties")
	float Damage;
};
