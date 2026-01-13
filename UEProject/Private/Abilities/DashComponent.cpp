// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DashComponent.h"

#include "ComponentUtils.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"


// Sets default values for this component's properties
UDashComponent::UDashComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDashComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDashComponent::Interact(const TScriptInterface<IInteractor>& Interactor)
{
	Super::Interact(Interactor);

	UE_LOG(LogTemp, Display, TEXT("In Dash"))

	APawn* InteractorPawn = Cast<APawn>(Interactor.GetObject());
	ACharacter* InteractorCharacter = Cast<ACharacter>(Interactor.GetObject());
	
	if (InteractorPawn == nullptr || InteractorCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractorPawn Error, Nullptr"))
		return;
	}

	//FVector3d CVelocity = InteractorCharacter->GetVelocity();
	float Direction = InteractorCharacter->GetActorForwardVector().Y/FMath::Abs(InteractorCharacter->GetActorForwardVector().Y);
	UE_LOG(LogTemp, Display, TEXT("%f"), Direction)
	
	float DashVelocity = DashMultiplier * BasePlayerMaxVelocity;

	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(InteractorPawn->GetMovementComponent());

	CharacterMovementComponent->StopMovementImmediately();
	InteractorCharacter->LaunchCharacter(FVector(DashVelocity, DashVelocity,0 ) * Direction, false, false);


	/*
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(InteractorPawn->GetMovementComponent());

	UE_LOG(LogTemp, Display, TEXT("%s"), *InteractorCharacter->GetName());
	
	if (CharacterMovementComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterMovementComponent Error, Nullptr"))
		return;
	}
	
	CharacterMovementComponent->AddImpulse(InteractorPawn->GetActorForwardVector().ForwardVector * DashStrength, true);
	UE_LOG(LogTemp, Display, TEXT("%s"), *(InteractorPawn->GetActorForwardVector().ForwardVector * DashStrength).ToString());
	*/
}

