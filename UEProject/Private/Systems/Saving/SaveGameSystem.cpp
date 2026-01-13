// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Saving/SaveGameSystem.h"

#include "Entity/Components/Actor/EntityStats.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/GameInstance/GameData.h"

USaveGameSystem::USaveGameSystem()
{
	UserIndex = 0;
	SaveSlotName = TEXT("BloodMaidenSaveFile");
	CurrentSaveData = {
		FVector(0.0f, 0.0f, 0.0f),
		0,  
		" ",
		{false}
	};
}

bool USaveGameSystem::SaveAllTheSelectedData(const TScriptInterface<IInteractor>& Interactor)
{
	AActor* PlayerActor = Cast<ACharacter>(Interactor.GetObject());
	UWorld* World = PlayerActor->GetWorld();
	UGameData* CurrentGameData = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameData>();

	UEntityStats* StatsComponent = nullptr;
	TArray<UActorComponent*> Components;
	PlayerActor->GetComponents(Components);
	for (UActorComponent* ChildComponent : Components)
	{
		if (ChildComponent->GetName() == "PlayerStats")
		{
			StatsComponent = Cast<UEntityStats>(ChildComponent);
		}
	}
	
	if (USaveGameSystem* SaveGameInstance = Cast<USaveGameSystem>(UGameplayStatics::CreateSaveGameObject(USaveGameSystem::StaticClass())))
	{
		CurrentSaveData.PlayerLocation = PlayerActor->GetActorLocation();
		CurrentSaveData.HealthAmount = StatsComponent->GetCurrentBlood();
		CurrentSaveData.SavedSceneName = World->GetName();
		CurrentSaveData.AudioMoresArray.Empty();
		CurrentSaveData.AudioMoresArray.SetNum(CurrentGameData->GetAudioMoreArray().Num());
		for (int i = 0; i < CurrentGameData->GetAudioMoreArray().Num(); i++)
		{
			CurrentSaveData.AudioMoresArray[i] = CurrentGameData->GetAudioMoreArray()[i];
		}
		return true;
	}
	return false;
}

bool USaveGameSystem::LoadAllTheSelectedData(const TScriptInterface<IInteractor>& Interactor) const
{
	AActor* PlayerActor = Cast<ACharacter>(Interactor.GetObject());
	UWorld* World = PlayerActor->GetWorld();
	UGameData* CurrentGameData = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameData>();

	UEntityStats* StatsComponent = nullptr;
	TArray<UActorComponent*> Components;
	PlayerActor->GetComponents(Components);
	for (UActorComponent* ChildComponent : Components)
	{
		if (ChildComponent->GetName() == "PlayerStats")
		{
			StatsComponent = Cast<UEntityStats>(ChildComponent);
		}
	}
	
	if (USaveGameSystem* LoadedGame = Cast<USaveGameSystem>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)))
	{
		StatsComponent->SetBlood(CurrentSaveData.HealthAmount);
		PlayerActor->SetActorLocation(CurrentSaveData.PlayerLocation);
		CurrentGameData->ResetAudioMoreArrayValues(99);
		for (int i = 0; i < CurrentSaveData.AudioMoresArray.Num(); i++)
		{
			 CurrentGameData->GetAudioMoreArray()[i] = CurrentSaveData.AudioMoresArray[i];
		}
		return true;
	}
	return false;
}

void USaveGameSystem::DeleteSaveData() const
{
	//Make sure the path I have is valid both in characters and in that the file path actually exists
	FString FilePath = FPaths::ProjectSavedDir() + "SaveGames/" + SaveSlotName + ".sav";
	if (FPaths::ValidatePath(FilePath) && FPaths::FileExists(FilePath))
	{
		IFileManager& FileManager = IFileManager::Get(); FileManager.Delete(*FilePath);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,"Failed To Delete Saved File");	
	}
}