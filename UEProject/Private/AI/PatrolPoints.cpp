// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PatrolPoints.h"

UPatrolPoints::UPatrolPoints()
{
	PrimaryComponentTick.bCanEverTick = false;
}

APatrolPoint* UPatrolPoints::GetNextPatrolPoint()
{
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No patrol points set."));
		return nullptr;
	}
	
	size_t NextIndex = (CurrentPatrolPointIndex + 1) % PatrolPoints.Num();
	
	TObjectPtr<APatrolPoint> NextPatrolPoint = PatrolPoints[NextIndex];
	CurrentPatrolPointIndex = NextIndex;
	
	return NextPatrolPoint;
}
