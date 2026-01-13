// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EventBusInterface.generated.h"

class IEventListenerInterface;

// This class does not need to be modified.
UINTERFACE(NotBlueprintable, BlueprintType)
class UEventBusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an EventBus.
 * Hopefully this never has to be made blueprintable, because then this will require a bit of refactoring as it doesn't-
 * use blueprint native events.
 */
class UEPROJECT_API IEventBusInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "EventBus")
	virtual void Publish(UObject* EventData, const UClass* EventType) = 0;
	
	virtual void Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) = 0;
	virtual void Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) = 0;
};
