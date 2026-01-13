// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityStats.h"
#include "Components/ActorComponent.h"
#include "StunnedState.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStunned, bool, IsStunned);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UStunnedState : public UActorComponent
{
	GENERATED_BODY()

public:
	UStunnedState();

public:
	UPROPERTY(BlueprintAssignable)
	FOnStunned OnStunned;

	UFUNCTION(BlueprintCallable)
	bool GetIsStunned() const { return IsStunned; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Stunned State")
	float StunDuration = 1.5f;
	
	virtual void BeginPlay() override;

private:
	FTimerHandle StunTimerHandle;
	
	UPROPERTY(BlueprintGetter="GetIsStunned")
	bool IsStunned = false;

	UFUNCTION()
	void EnterStunnedState(float DamageAmount, AController* DamageInstigator,
		AActor* DamageCauser, EDamageType DamageType);
	
	UFUNCTION()
	void ExitStunnedState();
	void NotifyStunnedState();
};
