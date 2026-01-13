// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/KnifeWeaponActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AKnifeWeaponActor::AKnifeWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DaggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActiveStaticMesh"));
	RootComponent = DaggerMesh;
	
	DaggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ActiveUBoxComponent"));
	DaggerBoxComponent->SetupAttachment(RootComponent);

	this->SetActorEnableCollision(false);
}

void AKnifeWeaponActor::InitializeDaggerVariables(const TScriptInterface<IInteractor>& Interactor)
{
	PlayerCharacter = Cast<ACharacter>(Interactor.GetObject());
	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is a Nullptr"))
		return;
	}
		
	TArray<UActorComponent*> ChildComponents;
	PlayerCharacter->GetComponents(ChildComponents);
	for (UActorComponent* ChildComponent : ChildComponents)
	{
		if (ChildComponent->GetName() == TEXT("CharMoveComp"))
		{
			PlayerCharacterMovement = Cast<UCharacterMovementComponent>(ChildComponent);
		}
	}
}

// Called when the game starts or when spawned
void AKnifeWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKnifeWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKnifeWeaponActor::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::Interact(Interactor);
	if (!bDaggerAttackActive)
	{
		InitializeDaggerVariables(Interactor);
		this->SetActorEnableCollision(true);
		bDaggerAttackActive = true;
	
		// if (PlayerCharacter->CanJump())
		// {
		// 	PlayerCharacterMovement->DisableMovement();	
		// }	
	}
}

void AKnifeWeaponActor::ReturnToHolster()
{
	this->SetActorEnableCollision(false);
	bDaggerAttackActive = false;
	//PlayerCharacterMovement->SetMovementMode(MOVE_Walking);
}

