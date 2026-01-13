// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestroyActorOnDeath.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UDestroyActorOnDeath : public UActorComponent
{
	GENERATED_BODY()

public:
	UDestroyActorOnDeath();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Death")
	float DelayBeforeDestroy = 1.0f;
	
	virtual void BeginPlay() override;

private:
	FTimerHandle DestroyActorHandle;
	
	UFUNCTION()
	void StartDestroyTimer();

	UFUNCTION()
	void EndDestroyTimer();
};
