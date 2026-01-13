#include "StateMachine/States/MenuState.h"
#include "Subsystems/GameInstance/GameData.h"
#include "Kismet/GameplayStatics.h"
#include "StateMachine/StateMachine.h"

void UMenuState::EnterState_Implementation()
{
	//UGameplayStatics::OpenLevel(this, TEXT("MainMenuLevel"));

	GetWorld()->GetGameInstance()->GetSubsystem<UGameData>()->bPauseTimer = true;
}

void UMenuState::UpdateState_Implementation()
{
	
}

void UMenuState::ExitState_Implementation()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameData>()->bPauseTimer = false;
}