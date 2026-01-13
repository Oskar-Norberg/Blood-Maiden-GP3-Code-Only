// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/PatrolPoint.h"

APatrolPoint::APatrolPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}
