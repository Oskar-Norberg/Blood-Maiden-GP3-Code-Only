// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Interfaces/Interactable.h"
#include "GrapplePoint.generated.h"

UCLASS()
class UEPROJECT_API AGrapplePoint : public AActor, public IInteractable
{
public:
	virtual void Interact(const TScriptInterface<IInteractor>& Interactor) override;

private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrapplePoint();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GrappleMeshComponent;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* ActiveMaterial;
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* DeactivatedMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool MFlipState = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool PlayerInRange = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MaterialFlipFlop();
	
};
