#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameData.generated.h"

UCLASS()
class UEPROJECT_API UGameData : public UGameInstanceSubsystem
{
	GENERATED_BODY()
 
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Data")
	bool bPauseTimer = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Data")
	TArray<bool> AudioMoresArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Data")
	bool bShouldLoadData = true;


public:
	UFUNCTION(BlueprintCallable, Category="Game Data")
	TArray<bool>& GetAudioMoreArray() { return AudioMoresArray; }

	UFUNCTION(BlueprintCallable, Category="Game Data")
	void AddToAudioMoreArray(int whichAudioGotTriggered)
	{
		if (AudioMoresArray.IsEmpty()) ResetAudioMoreArrayValues(99);
		AudioMoresArray[whichAudioGotTriggered] = true;
	}

	UFUNCTION(BlueprintCallable, Category="Game Data")
	void ResetAudioMoreArrayValues(int TotalAmountsOfAudioMores) { AudioMoresArray.SetNum(TotalAmountsOfAudioMores); for (bool b : AudioMoresArray) b = false; }
};