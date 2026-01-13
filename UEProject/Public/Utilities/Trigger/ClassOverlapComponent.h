// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ClassOverlapComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UClassOverlapComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UClassOverlapComponent();

	virtual void BeginPlay() override;

	virtual void OnRegister() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Trigger Properties")
	TSubclassOf<UActorComponent> OverlapComponentType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger Properties")
	TObjectPtr<UShapeComponent> TriggerShape;

	virtual void OnBeginOverlap(TObjectPtr<UActorComponent> OverlappedComponent);
	virtual void OnEndOverlap(TObjectPtr<UActorComponent> OverlappedComponent);
	
private:
	UFUNCTION()
	void OnBeginOverlapInternal(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEndInternal(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UActorComponent* GetComponentFromActor(AActor* Actor) const;
};
