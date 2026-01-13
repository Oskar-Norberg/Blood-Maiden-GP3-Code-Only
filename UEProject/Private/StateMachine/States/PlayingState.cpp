#include "StateMachine/States/PlayingState.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/GameInstance/GameData.h"

void UPlayingState::EnterState_Implementation()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameData>()->bPauseTimer = false;
}

void UPlayingState::UpdateState_Implementation()
{
	
}

void UPlayingState::ExitState_Implementation()
{
}