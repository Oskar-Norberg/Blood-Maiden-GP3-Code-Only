// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/CameraShake/CameraShakeDatabase.h"

TSubclassOf<UCameraShakeBase> UCameraShakeDatabase::GetCameraShake(float DamageAmount, AActor* DamagedActor,
	AActor* DamagedByActor, AController* DamageInstigator) const
{
	const TSubclassOf<UCameraShakeBase>* FoundClass = CameraShakeDataMap.Find(DamagedActor->GetClass());
	TSubclassOf<UCameraShakeBase> CameraShakeClass = FoundClass ? *FoundClass : nullptr;

	// TODO: This will need to support damage types in the future.

	return CameraShakeClass;
}
