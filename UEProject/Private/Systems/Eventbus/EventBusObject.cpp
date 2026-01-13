// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Eventbus/EventBusObject.h"
#include "Systems/Eventbus/Listener/Interface/EventListenerInterface.h"

void UEventBusObject::Publish(UObject* EventData, const UClass* EventType)
{
	TSet<TScriptInterface<IEventListenerInterface>>* ListenerSet = EventListeners.Find(EventType);
	
	if (ListenerSet)
	{
		for (const TScriptInterface<IEventListenerInterface>& Listener : *ListenerSet)
		{
			Listener.GetInterface()->Notify(EventData);
		}	
	}
}

void UEventBusObject::Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	TSet<TScriptInterface<IEventListenerInterface>>& ListenerSet = EventListeners.FindOrAdd(EventType);
	ListenerSet.Add(SomeCallback);
}

void UEventBusObject::Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	TSet<TScriptInterface<IEventListenerInterface>>* ListenerSet = EventListeners.Find(EventType);
	
	if (ListenerSet)
	{
		ListenerSet->Remove(SomeCallback);
	}
}
