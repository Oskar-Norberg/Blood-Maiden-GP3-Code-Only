// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Entity/Components/Actor/EntityStats.h"
#include "WeakState.generated.h"

class UEntityStats;
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeakState, bool, IsWeakState);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UWeakState : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeakState();
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnWeakState OnWeakState;

	UFUNCTION(BlueprintCallable)
	bool IsWeakState() const { return IsInWeakState; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeakStateBloodThreshold = 25.0f;

private:
	// TODO: i hate this and i am sorry
	bool JustEnteredWeakState;
	
	bool IsInWeakState;

	UPROPERTY()
	TObjectPtr<UEntityStats> EntityStats;
	
	UFUNCTION()
	void OnBloodChange(float NewBloodValue);

	UFUNCTION()
	void OnAttacked(float DamageAmount,AController* DamageInstigator, AActor* DamageCauser,
		EDamageType DamageType);

};
