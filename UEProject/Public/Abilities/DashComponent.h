// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BaseWeaponComponent.h"

#include "DashComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UEPROJECT_API UDashComponent : public UBaseWeaponComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDashComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BasePlayerMaxVelocity = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DashMultiplier = 10;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void Interact(const TScriptInterface<IInteractor>& Interactor) override;
};
