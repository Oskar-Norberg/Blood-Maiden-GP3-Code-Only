// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/TEMPSetWillFall.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UTEMPSetWillFall::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

EBTNodeResult::Type UTEMPSetWillFall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	const auto* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (!OwningPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("%s owning actor is null"), *GetName());
		return EBTNodeResult::Succeeded;
	}

	const FVector Location = OwningPawn->GetActorLocation();
	const FVector Direction = OwningPawn->GetActorForwardVector();

	// TODO: haha temporary terribleness
	const FVector CheckLocation = Location + Direction * 100.0f;
	const FVector LineTraceStart = CheckLocation;
	const FVector LineTraceEnd = CheckLocation - FVector::UpVector * 200.0f;

	FHitResult HitResult;
	bool DidHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);

	// TODO: disgusting
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("WillFall", !DidHit);

	return EBTNodeResult::Succeeded;
}
