// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemy/Base/AIController/BaseEnemyAIController.h"
#include "MeeleeEnemyAIController.generated.h"

UCLASS()
class UEPROJECT_API AMeeleeEnemyAIController : public ABaseEnemyAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeeleeEnemyAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
