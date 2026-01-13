// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/Trigger/ClassOverlapComponent.h"
#include "Components/ShapeComponent.h"


UClassOverlapComponent::UClassOverlapComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UClassOverlapComponent::OnRegister()
{
	Super::OnRegister();

	if (!TriggerShape)
	{
		UE_LOG(LogTemp, Error, TEXT("Trigger shape is null"));
		return;
	}
	
	TriggerShape->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}

void UClassOverlapComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerShape)
	{
		UE_LOG(LogTemp, Error, TEXT("Trigger shape is null"));
	}

	TriggerShape->OnComponentBeginOverlap.AddDynamic(this, &UClassOverlapComponent::OnBeginOverlapInternal);
	TriggerShape->OnComponentEndOverlap.AddDynamic(this, &UClassOverlapComponent::OnOverlapEndInternal);
}

void UClassOverlapComponent::OnBeginOverlapInternal(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* ComponentOnOverlapped = GetComponentFromActor(OtherActor);
	if (!ComponentOnOverlapped)
	{
		return;
	}
	
	OnBeginOverlap(ComponentOnOverlapped);
}

void UClassOverlapComponent::OnOverlapEndInternal(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto* ComponentOnOverlapped = GetComponentFromActor(OtherActor);
	if (!ComponentOnOverlapped)
	{
		return;
	}
	
	OnEndOverlap(ComponentOnOverlapped);
}

UActorComponent* UClassOverlapComponent::GetComponentFromActor(AActor* Actor) const
{
	return Actor->GetComponentByClass(OverlapComponentType);
}

// God I wish pure virtuals were a thing in Unreal
void UClassOverlapComponent::OnBeginOverlap(TObjectPtr<UActorComponent> OverlappedComponent)
{
}

void UClassOverlapComponent::OnEndOverlap(TObjectPtr<UActorComponent> OverlappedComponent)
{
}