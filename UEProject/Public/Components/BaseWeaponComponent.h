#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Interactable.h"
#include "BaseWeaponComponent.generated.h"


UCLASS()
class UEPROJECT_API UBaseWeaponComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact(const TScriptInterface<IInteractor>& Interactor) override;
	virtual void InteractBegin(const TScriptInterface<IInteractor>& Interactor) override;
	virtual void InteractEnd(const TScriptInterface<IInteractor>& Interactor) override;
};