// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TEMPSetWillFall.generated.h"

/**
 * TODO: This class is a TEMPORARY solution to flag if the AI will fall.
 * This NEEDS to be refactored into a query/service.
 * This is a testament to my *expertise* in Unreal Engine
 */
UCLASS()
class UEPROJECT_API UTEMPSetWillFall : public UBTTaskNode
{
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
