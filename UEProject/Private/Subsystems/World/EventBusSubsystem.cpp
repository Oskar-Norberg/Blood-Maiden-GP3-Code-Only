// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystems/World/EventBusSubsystem.h"
#include "Systems/Eventbus/EventBusObject.h"

void UEventBusSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	EventBusObject = NewObject<UEventBusObject>(this, UEventBusObject::StaticClass());
}

void UEventBusSubsystem::Publish(UObject* EventData, const UClass* EventType)
{
	EventBusObject->Publish(EventData, EventType);
}

void UEventBusSubsystem::Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	EventBusObject->Subscribe(EventType, SomeCallback);
}

void UEventBusSubsystem::Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	EventBusObject->Unsubscribe(EventType, SomeCallback);
}
