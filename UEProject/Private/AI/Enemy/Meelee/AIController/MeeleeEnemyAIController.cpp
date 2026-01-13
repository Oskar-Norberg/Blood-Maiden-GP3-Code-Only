// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemy/Meelee/AIController/MeeleeEnemyAIController.h"


// Sets default values
AMeeleeEnemyAIController::AMeeleeEnemyAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeeleeEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeeleeEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

