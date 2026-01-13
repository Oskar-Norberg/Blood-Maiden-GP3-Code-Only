#include "Player/Components/Actor/PlayerDeathComponent.h"
#include "Player/Components/Actor/PlayerStats.h"
#include "StateMachine/StateMachine.h"
#include "StateMachine/States/GameOverState.h"

UPlayerDeathComponent::UPlayerDeathComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerDeathComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerEntityStatsComp = GetOwner()->GetComponentByClass(UPlayerStats::StaticClass());
	
	FTimerHandle DelayTimer;
	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this,
		&UPlayerDeathComponent::BindDeathEvent, EventBindDelay);

}

void UPlayerDeathComponent::OnDeath()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UStateMachine>()->SetState(UGameOverState::StaticClass());
	Cast<UPlayerStats>(PlayerEntityStatsComp)->OnDeath.RemoveDynamic(this, &UPlayerDeathComponent::OnDeath);
}

void UPlayerDeathComponent::BindDeathEvent()
{
	Cast<UPlayerStats>(PlayerEntityStatsComp)->OnDeath.AddDynamic(this, &UPlayerDeathComponent::OnDeath);
}

