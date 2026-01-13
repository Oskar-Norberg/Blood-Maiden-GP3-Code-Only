// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Eventbus/Listener/Interface/EventListenerInterface.h"
#include "UObject/Object.h"
#include "UEventListener.generated.h"

class IEventBusInterface;
class UEventBusObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDelegate, UObject*, EventData);

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UEventListener : public UActorComponent, public IEventListenerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FEventDelegate OnEventReceived;

public:
	UFUNCTION(BlueprintCallable, Category = "EventBus|Listener")
	void Init(TScriptInterface<IEventBusInterface> SomeEventBus, const UClass* EventType);
	UFUNCTION(BlueprintCallable, Category = "EventBus|Listener")
	void ActivateListener();
	UFUNCTION(BlueprintCallable, Category = "EventBus|Listener")
	void DeactivateListener();

private:
	UPROPERTY()
	const UClass* RegisteredEventType;
	UPROPERTY()
	TScriptInterface<IEventBusInterface> RegisteredEventBus;

	virtual void Notify(TObjectPtr<UObject> EventData) override;
};
