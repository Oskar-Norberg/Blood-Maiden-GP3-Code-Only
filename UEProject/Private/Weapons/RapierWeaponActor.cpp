// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RapierWeaponActor.h"

#include "ShaderPrintParameters.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ARapierWeaponActor::ARapierWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RapierMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RapierStaticMesh"));
	RootComponent = RapierMeshComponent;
	
	RapierBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ActiveUBoxComponent"));
	RapierBoxComponent->SetupAttachment(RootComponent);
	this->SetActorEnableCollision(false);
}

void ARapierWeaponActor::GetOwnerHierarchy()
{
	AActor* ThisOwner = this;
	bool HaveParent = true;
	while (HaveParent)
	{
		AActor* ParentOwner = ThisOwner->GetAttachParentActor();
		if (IsValid(ParentOwner))
		{
			ThisOwner = ParentOwner;
		}
		else
		{
			OwnerActor = ThisOwner;
			HaveParent = false;
		}
	}
}
// Called when the game starts or when spawned
void ARapierWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	GetOwnerHierarchy();
}
// Called every frame
void ARapierWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARapierWeaponActor::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::Interact(Interactor);
	bRapierAttackAnimationActive = true;
	this->SetActorEnableCollision(true);
}

void ARapierWeaponActor::ReturnToHolster()
{
	this->SetActorEnableCollision(false);
	bRapierAttackAnimationActive = false;
}

