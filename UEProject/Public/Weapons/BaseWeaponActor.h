// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "BaseWeaponActor.generated.h"

UCLASS(ClassGroup="Components", meta=(BlueprintSpawnableComponent), Blueprintable)
class UEPROJECT_API ABaseWeaponActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeaponActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float AttackDamage = 10.0f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(const TScriptInterface<IInteractor>& Interactor) override;
	virtual void InteractBegin(const TScriptInterface<IInteractor>& Interactor) override;
	virtual void InteractEnd(const TScriptInterface<IInteractor>& Interactor) override;
};
