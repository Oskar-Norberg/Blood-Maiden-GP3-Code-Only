// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"
#include "Interfaces/Interactor.h"


// Add default functionality here for any IInteractable functions that are not pure virtual.
void IInteractable::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	OnInteractionEvent.Broadcast();
}

void IInteractable::InteractBegin(const TScriptInterface<IInteractor>& Interactor)
{
	OnInteractionBeginEvent.Broadcast();
}

void IInteractable::InteractEnd(const TScriptInterface<IInteractor>& Interactor)
{
	OnInteractionEndEvent.Broadcast();
}