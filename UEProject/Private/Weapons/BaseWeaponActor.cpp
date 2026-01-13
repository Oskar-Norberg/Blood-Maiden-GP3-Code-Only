#include "Weapons/BaseWeaponActor.h"

// Sets default values
ABaseWeaponActor::ABaseWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeaponActor::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::InteractBegin(Interactor);
}

void ABaseWeaponActor::InteractBegin(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::InteractBegin(Interactor);
}

void ABaseWeaponActor::InteractEnd(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::InteractEnd(Interactor);
}