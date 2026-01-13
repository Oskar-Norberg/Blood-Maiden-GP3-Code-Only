#include "StateMachine/States/GameOverState.h"
#include "Subsystems/GameInstance/GameData.h"
#include "Kismet/GameplayStatics.h"

class UGameData;

void UGameOverState::EnterState_Implementation()
{
	//UGameplayStatics::OpenLevel(this, TEXT("ResultLevel"));
	
	UE_LOG(LogTemp, Error, TEXT("Game Over State"));

	GetWorld()->GetGameInstance()->GetSubsystem<UGameData>()->bPauseTimer = true;
}

void UGameOverState::UpdateState_Implementation()
{
}

void UGameOverState::ExitState_Implementation()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameData>()->bPauseTimer = false;
}