// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Systems/Eventbus/Listener/Interface/EventBusInterface.h"
#include "EventBusSubsystem.generated.h"

class UEventBusObject;

/**
 * 
 */
UCLASS()
class UEPROJECT_API UEventBusSubsystem : public UWorldSubsystem, public IEventBusInterface
{
	GENERATED_BODY()

public:
	virtual void Publish(UObject* EventData, const UClass* EventType) override;

	virtual void Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) override;
	virtual void Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) override;

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UPROPERTY()
	TObjectPtr<UEventBusObject> EventBusObject;
};
