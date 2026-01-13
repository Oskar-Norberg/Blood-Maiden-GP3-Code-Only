// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CameraShakeDatabase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UEPROJECT_API UCameraShakeDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Shake")
	TMap<TSubclassOf<AActor>, TSubclassOf<UCameraShakeBase>> CameraShakeDataMap;
	
	UFUNCTION(BlueprintCallable, Category="Camera Shake")
	TSubclassOf<UCameraShakeBase> GetCameraShake(float DamageAmount, AActor* DamagedActor, AActor* DamagedByActor, AController* DamageInstigator) const;
};
