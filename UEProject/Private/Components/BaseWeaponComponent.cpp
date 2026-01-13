#include "Components/BaseWeaponComponent.h"

UBaseWeaponComponent::UBaseWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseWeaponComponent::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::Interact(Interactor);
}

void UBaseWeaponComponent::InteractBegin(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::InteractBegin(Interactor);
}

void UBaseWeaponComponent::InteractEnd(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::InteractEnd(Interactor);
}