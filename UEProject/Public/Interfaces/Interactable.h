// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class IInteractor;

// This class does not need to be modified.
UINTERFACE(NotBlueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteraction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionBegin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionEnd);

class UEPROJECT_API IInteractable
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FOnInteraction OnInteractionEvent;
	FOnInteractionBegin OnInteractionBeginEvent;
	FOnInteractionEnd OnInteractionEndEvent;
	
	UFUNCTION(BlueprintCallable)
	virtual void Interact(const TScriptInterface<IInteractor>& Interactor);

	UFUNCTION(BlueprintCallable)
	virtual void InteractBegin(const TScriptInterface<IInteractor>& Interactor);

	UFUNCTION(BlueprintCallable)
	virtual void InteractEnd(const TScriptInterface<IInteractor>& Interactor);
};