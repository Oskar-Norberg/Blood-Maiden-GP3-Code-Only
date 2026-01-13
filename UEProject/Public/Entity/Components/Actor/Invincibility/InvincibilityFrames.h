// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Interactable.h"
#include "InvincibilityFrames.generated.h"

class UEntityStats;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInvincibilityChanged, bool, IsInvincible);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UInvincibilityFrames : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:
	FOnInvincibilityChanged OnInvincibilityChanged;
public:
	virtual void Interact(const TScriptInterface<IInteractor>& Interactor) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Invincibility Setup")
	float InvincibilityDuration = 1.0f;

private:
	UPROPERTY()
	TObjectPtr<UEntityStats> InteractorStats;
	
	FTimerHandle InvincibilityTimerHandle;

	UFUNCTION()
	void EndInvincibility();
	void NotifyInvincibilityChanged() const;
};