// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KnifeWeaponActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UEPROJECT_API AKnifeWeaponActor : public ABaseWeaponActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DaggerMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DaggerBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDaggerAttackActive = false;
	
	// Sets default values for this actor's properties
	AKnifeWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TObjectPtr<UCharacterMovementComponent> PlayerCharacterMovement = nullptr;
	TObjectPtr<ACharacter> PlayerCharacter = nullptr;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// ReSharper disable once CppEnforceOverridingFunctionStyle
	void Interact(const TScriptInterface<IInteractor>& Interactor) override;

	UFUNCTION(BlueprintCallable)
	void ReturnToHolster();

	UFUNCTION(BlueprintCallable)
	void InitializeDaggerVariables(const TScriptInterface<IInteractor>& Interactor);
	
};
