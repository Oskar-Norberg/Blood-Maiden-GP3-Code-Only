#include "Gameplay/Triggers/LevelLoadingTrigger.h"
#include "Kismet/GameplayStatics.h"

ALevelLoadingTrigger::ALevelLoadingTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelLoadingTrigger::BeginPlay()
{
	Super::BeginPlay();

	
}

void ALevelLoadingTrigger::LoadNextLevel()
{
	//Pause player movement?
	UGameplayStatics::OpenLevel(this, LevelName);
	//Resume player movement?
}

void ALevelLoadingTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
