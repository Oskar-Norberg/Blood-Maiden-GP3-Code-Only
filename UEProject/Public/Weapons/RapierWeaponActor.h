// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponActor.h"
#include "RapierWeaponActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UEPROJECT_API ARapierWeaponActor : public ABaseWeaponActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RapierMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* RapierBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRapierAttackAnimationActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	class USkeletalMesh* SkeletalMesh;
	
	// Sets default values for this actor's properties
	ARapierWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// I marked these with UPROPERTY so they wont be garbage collected - Oskar
	UPROPERTY()
	TObjectPtr<AActor> OwnerActor;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// ReSharper disable once CppEnforceOverridingFunctionStyle
	void Interact(const TScriptInterface<IInteractor>& Interactor) override;
	void GetOwnerHierarchy();
 
	UFUNCTION(BlueprintCallable)
	void ReturnToHolster();
};
