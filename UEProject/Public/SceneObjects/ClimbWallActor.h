// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ClimbWallActor.generated.h"

UCLASS()
class UEPROJECT_API AClimbWallActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ClimbWallStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ClimbWallBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ClimbUpAndDownWallSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractWithClimbableWallDistance = 0.0f;
	
	// Sets default values for this actor's properties
	AClimbWallActor();

protected:
	TObjectPtr<ACharacter> PlayerCharacter = nullptr;
	TObjectPtr<UCharacterMovementComponent> PlayerCharacterMovement = nullptr;
	float DefaultGravityScale = 0.0f;
	bool bTryToStartClimbing = false;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetClimbWallMovement(bool NewBoolValue)
	{
		//PlayerCharacter->ClimbWallMovement = NewBoolValue;
	}
	
	UFUNCTION(BlueprintCallable)
	bool GetClimbWallMovement()
	{
		return true; //PlayerCharacter->ClimbWallMovement;
	}

	UFUNCTION(BlueprintCallable)
	void MovePlayerUp();
	UFUNCTION(BlueprintCallable)
	void MovePlayerDown();

	UFUNCTION(BlueprintCallable)
	void TryToStartClimbing();
};
