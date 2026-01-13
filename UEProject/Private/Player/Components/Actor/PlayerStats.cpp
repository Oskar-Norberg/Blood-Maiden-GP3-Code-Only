#include "Player/Components/Actor/PlayerStats.h"

void UPlayerStats::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerStats::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RemoveBlood(BloodLossRatePerSeconds * DeltaTime);
}
