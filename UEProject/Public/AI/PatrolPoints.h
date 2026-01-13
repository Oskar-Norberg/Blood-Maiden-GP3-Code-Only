// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolPoints.generated.h"


class APatrolPoint;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UPatrolPoints : public UActorComponent
{
	GENERATED_BODY()

public:
	UPatrolPoints();

	UFUNCTION(BlueprintCallable)
	APatrolPoint* GetNextPatrolPoint();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Patrol Points")
	TArray<TObjectPtr<APatrolPoint>> PatrolPoints;

private:
	size_t CurrentPatrolPointIndex = 0;
};
