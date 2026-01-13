#include "StateMachine/States/PauseState.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/GameInstance/GameData.h"

void UPauseState::EnterState_Implementation()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f); //idk what this does lol
	
	GetWorld()->GetGameInstance()->GetSubsystem<UGameData>()->bPauseTimer = true;
}

void UPauseState::UpdateState_Implementation()
{
}

void UPauseState::ExitState_Implementation()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	
	GetWorld()->GetGameInstance()->GetSubsystem<UGameData>()->bPauseTimer = false;
}