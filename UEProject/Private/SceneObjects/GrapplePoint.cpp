// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneObjects/GrapplePoint.h"


void AGrapplePoint::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::Interact(Interactor);

	MaterialFlipFlop();
}

// Sets default values
AGrapplePoint::AGrapplePoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrappleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = GrappleMeshComponent;

	//Set Cube Mesh to Static Component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeAsset.Succeeded())
	{
		GrappleMeshComponent->SetStaticMesh(CubeAsset.Object);
	}

	//Set Initial Cube Material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/Interactable/M_GrappleOutOfRange.M_GrappleOutOfRange"));
	if (MaterialAsset.Succeeded())
	{
		GrappleMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}

	//Set Cube Tag
	GrappleMeshComponent->ComponentTags.Add(FName("Grapple"));

	//Set Cube Scale
	GrappleMeshComponent->SetWorldScale3D(FVector(.5f,.5f,.5f));

	//Set Cubes Collisions
	GrappleMeshComponent->SetCollisionProfileName(TEXT("NoCollision")); // or "OverlapAll"
	GrappleMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GrappleMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	GrappleMeshComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AGrapplePoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGrapplePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AGrapplePoint::MaterialFlipFlop()
{
	if (MFlipState)
	{
		//The Grapple is Deactive
		GrappleMeshComponent->SetMaterial(0, DeactivatedMaterial);
		PlayerInRange = false;
		MFlipState = false;
	}
	else
	{
		//The Grapple is Active
		GrappleMeshComponent->SetMaterial(0, ActiveMaterial);
		PlayerInRange = true;
		MFlipState = true;
	}
}

