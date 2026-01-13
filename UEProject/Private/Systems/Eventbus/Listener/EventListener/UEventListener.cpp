// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Eventbus/Listener/EventListener/UEventListener.h"
#include "Systems/Eventbus/Listener/Interface/EventBusInterface.h"

void UEventListener::Notify(TObjectPtr<UObject> EventData)
{
	OnEventReceived.Broadcast(EventData.Get());
}

void UEventListener::Init(TScriptInterface<IEventBusInterface> SomeEventBus, const UClass* EventType)
{
	RegisteredEventBus = SomeEventBus;
	RegisteredEventType = EventType;
}

void UEventListener::ActivateListener()
{
	RegisteredEventBus->Subscribe(RegisteredEventType, this);
}

void UEventListener::DeactivateListener()
{
	RegisteredEventBus->Unsubscribe(RegisteredEventType, this);
}
