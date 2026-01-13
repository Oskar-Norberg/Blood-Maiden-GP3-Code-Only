// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneObjects/BloodDoor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "FrameTypes.h"


// Sets default values
ABloodDoor::ABloodDoor()
{ 
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DoorObjectSceneComponent = CreateDefaultSubobject<USceneComponent>("DoorObjectSceneComponent");
	SetRootComponent(DoorObjectSceneComponent);
	
	DoorHolderSceneComponent = CreateDefaultSubobject<USceneComponent>("DoorHolder");
	DoorHolderSceneComponent->SetupAttachment(DoorObjectSceneComponent);
	//SetRootComponent(DoorHolderSceneComponent);
	
	BloodDoorStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BloodDoorStaticMesh"));
	BloodDoorStaticMeshComponent->SetupAttachment(DoorHolderSceneComponent);
	
	BloodDoorBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BloodDoorUBoxComponent"));
	BloodDoorBoxComponent->SetupAttachment(BloodDoorStaticMeshComponent);

	BloodDoorFrameStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BloodDoorFrameStaticMesh"));
	BloodDoorFrameStaticMeshComponent->SetupAttachment(DoorObjectSceneComponent);
}

void ABloodDoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TArray<USceneComponent*> ChildComponents;
	GetRootComponent()->GetChildrenComponents(true,ChildComponents);
	for (USceneComponent* ChildComponent : ChildComponents)
	{
		if (ChildComponent->GetName() == "BloodDoorWidget")
		{
			BloodDoorWidgetComponent = Cast<USceneComponent>(ChildComponent);
		}
	}
	if (IsValid(BloodDoorWidgetComponent))
	{
		FVector WidgetLocation = BloodDoorWidgetComponent->GetRelativeLocation();
		WidgetLocation.Y = 0.0f;
		if (bInvertDoorMovement) WidgetLocation.Y = WidgetLocation.Y - 100.0f;
		else if (!bInvertDoorMovement) WidgetLocation.Y = WidgetLocation.Y + 100.0f;
		BloodDoorWidgetComponent->SetRelativeLocation(WidgetLocation);
	}
}
// Called when the game starts or when spawned
void ABloodDoor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABloodDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (BloodDoorOpen)
	{
		if (bInvertDoorMovement)
		{
			FRotator DoorRotation = DoorHolderSceneComponent->GetComponentRotation();
			if (DoorRotation.Yaw <= BloodDoorStartRotation.Yaw - BloodDoorMoveDistance) BloodDoorClose = false;
			else
			{
				FQuat NewRotation = FQuat::Slerp(DoorRotation.Quaternion(), FRotator(DoorRotation.Pitch, DoorRotation.Yaw - (BloodDoorMoveSpeed / 10) , DoorRotation.Roll).Quaternion(), 0.5f);
				DoorHolderSceneComponent->SetWorldRotation(NewRotation);
			}
		}
		else
		{
			FRotator DoorRotation = DoorHolderSceneComponent->GetComponentRotation();
			if (DoorRotation.Yaw >= BloodDoorStartRotation.Yaw + BloodDoorMoveDistance) BloodDoorOpen = false;
			else
			{
				FQuat NewRotation = FQuat::Slerp(DoorRotation.Quaternion(), FRotator(DoorRotation.Pitch, DoorRotation.Yaw + (BloodDoorMoveSpeed / 10) , DoorRotation.Roll).Quaternion(), 0.5f);
				DoorHolderSceneComponent->SetWorldRotation(NewRotation);
			}	
		}
	}

	if (BloodDoorClose)
	{
		FRotator DoorRotation = DoorHolderSceneComponent->GetComponentRotation();
		if (DoorRotation.Yaw <= BloodDoorStartRotation.Yaw - BloodDoorMoveDistance) BloodDoorClose = false;
		else
		{
			FQuat NewRotation = FQuat::Slerp(DoorRotation.Quaternion(), FRotator(DoorRotation.Pitch, DoorRotation.Yaw - (BloodDoorMoveSpeed / 10) , DoorRotation.Roll).Quaternion(), 0.5f);
			DoorHolderSceneComponent->SetWorldRotation(NewRotation);
		}
	}
}

AActor* ABloodDoor::TryToOpenBloodDoor(const TScriptInterface<IInteractor>& Interactor)
{
	PlayerCharacter = Cast<ACharacter>(Interactor.GetObject());
	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is a Nullptr"))
		return nullptr;
	}
	FVector PlayerCharacterYPos = FVector(0,PlayerCharacter->GetActorLocation().Y,0);
	FVector BloodDoorYPos = FVector(0,BloodDoorStaticMeshComponent->GetComponentLocation().Y,0);
	if (UE::Geometry::Distance(PlayerCharacterYPos, BloodDoorYPos) <= BloodDoorInteractRange)
	{
		if (!BloodDoorSpendCost)
		{
			TArray<UActorComponent*> Components;
			PlayerCharacter->GetComponents(Components);
			for (UActorComponent* ChildComponent : Components)
			{
				if (ChildComponent->GetName() == "PlayerStats")
				{
					StatsComponent = Cast<UPlayerStats>(ChildComponent);
				}
			}
			if (!bWantTakeRandomBloodValue)
			{
				if (CheckIfEnoughBloodPoints())
				{
					BloodDoorSpendCost = true;
					OpenBloodDoor();
				}
			}
			else
			{
				BloodDoorSpendCost = true;
				TakeRandomBloodPoints();
			}
		}	
	}
		
	return this;
}

bool ABloodDoor::CheckIfEnoughBloodPoints()
{
	if (IsValid(StatsComponent))
	{
		float PlayerCurrentBlood = StatsComponent->GetCurrentBlood();
		if (PlayerCurrentBlood >= RequiredBloodAmount)
		{
			StatsComponent->RemoveBlood(RequiredBloodAmount);
			return true;
		}
	}
	return false;
}

void ABloodDoor::TakeRandomBloodPoints()
{
	if (IsValid(StatsComponent))
	{
		float PlayerCurrentBlood = StatsComponent->GetCurrentBlood();
		int RandomTakeAwayValue = FMath::RandRange(30, 70);
		float RandomTakeAwayValueFloat =  static_cast<float>(RandomTakeAwayValue) / 100;
		PlayerCurrentBlood = PlayerCurrentBlood * RandomTakeAwayValueFloat;
		StatsComponent->RemoveBlood(PlayerCurrentBlood);
		OpenBloodDoor();
	}
}

void ABloodDoor::OpenBloodDoor()
{
	BloodDoorStartRotation = DoorHolderSceneComponent->GetComponentRotation();
	BloodDoorOpen = true;
}

void ABloodDoor::CloseBloodDoor()
{
	BloodDoorStartRotation = DoorHolderSceneComponent->GetComponentRotation();
	BloodDoorClose = true;
}

