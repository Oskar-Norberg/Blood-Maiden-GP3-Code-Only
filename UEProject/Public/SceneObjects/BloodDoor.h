// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/Components/Actor/PlayerStats.h"
#include "Interfaces/Interactable.h"
#include "BloodDoor.generated.h"

UCLASS()
class UEPROJECT_API ABloodDoor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DoorHolderSceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BloodDoorStaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BloodDoorBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BloodDoorFrameStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* BloodDoorWidgetComponent;
	// Sets default values for this actor's properties
	ABloodDoor();

	
protected:
	TObjectPtr<APawn> PlayerCharacter = nullptr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AActor* TryToOpenBloodDoor(const TScriptInterface<IInteractor>& Interactor);
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfEnoughBloodPoints();

	UFUNCTION(BlueprintCallable)
	void TakeRandomBloodPoints();
	
	UFUNCTION(BlueprintCallable)
	void OpenBloodDoor();

	UFUNCTION(BlueprintCallable)
	void CloseBloodDoor();

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RequiredBloodAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWantTakeRandomBloodValue = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) //This is funny
	uint8 bInvertDoorMovement:1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BloodDoorMoveDistance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BloodDoorMoveSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BloodDoorInteractRange = 0.0f;
	
private:
	UPlayerStats* StatsComponent = nullptr;

	bool BloodDoorOpen = false;
	bool BloodDoorClose = false;
	bool BloodDoorSpendCost = false;
	float MoveBloodDoorSpeed = 0.0f;

	FRotator BloodDoorStartRotation;
};
