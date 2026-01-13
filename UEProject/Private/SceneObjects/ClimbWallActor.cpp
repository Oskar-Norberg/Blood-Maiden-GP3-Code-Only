// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneObjects/ClimbWallActor.h"
#include "Components/BoxComponent.h"
#include "FrameTypes.h"


// Sets default values
AClimbWallActor::AClimbWallActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ClimbWallStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClimbWallStaticMesh"));
	RootComponent = ClimbWallStaticMeshComponent;

	ClimbWallBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ClimbWallUBoxComponent"));
	ClimbWallBoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AClimbWallActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();

	if (PlayerCharacter == nullptr)
	{
		// TODO: Avoid using GetFirstPlayerController();
		UE_LOG(LogTemp, Display, TEXT("That shouldnt've happened"));
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
	DefaultGravityScale = PlayerCharacterMovement->GravityScale;
}

// Called every frame
void AClimbWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AClimbWallActor::TryToStartClimbing()
{
	if (PlayerCharacter == nullptr)
	{
		// TODO: Avoid using GetFirstPlayerController();
		UE_LOG(LogTemp, Display, TEXT("That shouldnt've happened"));
		return;
	}
	
	FVector PlayerCharacterYPos = FVector(0,PlayerCharacter->GetActorLocation().Y,0);
	FVector ClimbWallYPos = FVector(0,this->GetActorLocation().Y,0);
	if (UE::Geometry::Distance(PlayerCharacterYPos, ClimbWallYPos) >= InteractWithClimbableWallDistance) return;
	// if(PlayerCharacter->ClimbWallMovement)
	// {
	// 	PlayerCharacterMovement->GravityScale = DefaultGravityScale;
	// 	PlayerCharacter->ClimbWallMovement = false;
	// }
	// else
	// {
	// 	//PlayerCharacter->ClimbWallMovement = true;
	// 	this->SetActorEnableCollision(false);
	// 	this->SetActorEnableCollision(true);
	// }
}

void AClimbWallActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// if (OtherActor == PlayerCharacter && PlayerCharacter->ClimbWallMovement)
	// {
	// 	PlayerCharacterMovement->GravityScale = 0.0f;
	// }
}

void AClimbWallActor::NotifyActorEndOverlap(AActor* OtherActor) 
{
	if (PlayerCharacter == nullptr)
	{
		// TODO: Avoid using GetFirstPlayerController();
		UE_LOG(LogTemp, Display, TEXT("That shouldnt've happened"));
		return;
	}
	if (OtherActor == PlayerCharacter)
	{
		PlayerCharacterMovement->GravityScale = DefaultGravityScale;
	}
}

void AClimbWallActor::MovePlayerUp()
{
	if (PlayerCharacter == nullptr)
	{
		// TODO: Avoid using GetFirstPlayerController();
		UE_LOG(LogTemp, Display, TEXT("That shouldnt've happened"));
		return;
	}
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	PlayerLocation.Z = PlayerLocation.Z + ClimbUpAndDownWallSpeed;
	PlayerCharacter->SetActorLocation(PlayerLocation);
}

void AClimbWallActor::MovePlayerDown()
{
	if (PlayerCharacter == nullptr)
	{
		// TODO: Avoid using GetFirstPlayerController();
		UE_LOG(LogTemp, Display, TEXT("That shouldnt've happened"));
		return;
	}
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	PlayerLocation.Z = PlayerLocation.Z - ClimbUpAndDownWallSpeed;
	PlayerCharacter->SetActorLocation(PlayerLocation);
}


