// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/Interactor.h"
#include "GrappleActor.generated.h"

class UNiagaraSystem;
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSuccessfullGrapple, bool, grappled, FVector, GrapplePoint);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API AGrappleActor : public AActor, public IInteractable, public IInteractor
{
	GENERATED_BODY()

public:
	AGrappleActor();

	UPROPERTY(BlueprintAssignable)
	FOnSuccessfullGrapple OnSuccessfullGrapple;
	
	UPROPERTY(VisibleAnywhere, Blueprintable, Category = "Collision")
	USphereComponent* CollisionSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grapple")
	float Division = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grapple")
	float MinPower = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grapple")
	float GrappleRadius = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grapple")
	float GrapplePower = 3000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grapple")
	float DelayBeforeGrapple = 0.25f;
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	AActor* TargetedGrapple = nullptr;

	UPROPERTY(VisibleAnywhere)
	FVector Direction;

	UPROPERTY(VisibleAnywhere)
	ACharacter* InteractorCharacter;
	
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(const TScriptInterface<IInteractor>& Interactor) override;

private:
	FTimerHandle GrappleDelayHandle;
};
