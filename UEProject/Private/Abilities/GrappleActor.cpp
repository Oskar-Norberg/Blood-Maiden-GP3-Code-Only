// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GrappleActor.h"
#include "GameFramework/Character.h"
#include "SceneObjects/GrapplePoint.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AGrappleActor::AGrappleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;

	CollisionSphere->InitSphereRadius(GrappleRadius);
	CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AGrappleActor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->SetSphereRadius(GrappleRadius);
	
}

void AGrappleActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Enter overlap with grapple point
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->Tags.Contains("Grapple"))
	{
		UE_LOG(LogTemp, Display, TEXT("Grapple Enter"))
		AGrapplePoint* GPoint = Cast<AGrapplePoint>(OtherActor);

		GPoint->Interact(this);
		TargetedGrapple = OtherActor;
	}
}

void AGrappleActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	//Exit overlap with grapple point
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor->Tags.Contains("Grapple"))
	{
		UE_LOG(LogTemp, Display, TEXT("Grapple Exit"))
		AGrapplePoint* GPoint = Cast<AGrapplePoint>(OtherActor);
		if (TargetedGrapple == OtherActor)
		{
			TargetedGrapple = nullptr;
		}
		GPoint->Interact(this);
	}
}

// Called every frame
void AGrappleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrappleActor::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	IInteractable::Interact(Interactor);
	
	if (!TargetedGrapple)
	{
		UE_LOG(LogTemp, Display, TEXT("Grapple Point is null"))
		OnSuccessfullGrapple.Broadcast(false, FVector::Zero());
		return;
	}
	
	OnSuccessfullGrapple.Broadcast(true, TargetedGrapple->GetActorLocation());
	
	AActor* InteractorActor = Cast<AActor>(Interactor.GetObject());
	Direction = TargetedGrapple->GetActorLocation() - InteractorActor->GetActorLocation();
	Direction /= Division;
	
	InteractorCharacter = Cast<ACharacter>(Interactor.GetObject());
	
	if (InteractorCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractorCharacter Error, Nullptr"))
		return;
	}
	
	
	FVector GrapplePointDown =  FVector(0,0, TargetedGrapple->GetActorLocation().Z - InteractorCharacter->GetActorLocation().Z).GetSafeNormal();

	float DotProductVector =  FVector::DotProduct(Direction.GetSafeNormal(), GrapplePointDown);
	float CurveFactor = FMath::Pow(2 ,-abs(FMath::Pow(DotProductVector - 0.5f, 2)/0.03f)-1.32f) + 1;

	UE_LOG(LogTemp, Display, TEXT("Curve Factor: %f"), CurveFactor)
	
	
	FVector TotalPower = (Direction * CurveFactor) * GrapplePower;

	UE_LOG(LogTemp, Display, TEXT("Base Power: %f"), TotalPower.Length())
	
	if (TotalPower.Length() < MinPower)
	{
		UE_LOG(LogTemp, Display, TEXT("MinPower"))
		TotalPower = (TotalPower.GetSafeNormal() * MinPower) * CurveFactor;

		UE_LOG(LogTemp, Display, TEXT("After Clamp: %f"), TotalPower.Length())
	}


	GetWorld()->GetTimerManager().SetTimer(GrappleDelayHandle, [this, TotalPower]()
		{InteractorCharacter->LaunchCharacter(TotalPower, true, true);}, DelayBeforeGrapple, false
		);
}
