// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameSystem.generated.h"

USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PlayerLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SavedSceneName = " ";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> AudioMoresArray;
};
/**
 * 
 */
UCLASS()
class UEPROJECT_API USaveGameSystem : public USaveGame
{
	GENERATED_BODY()
	
	public:
	
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Saving)
		int32 UserIndex;

		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Saving)
		FString SavedSceneName;
		
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Saving)
		FSaveData CurrentSaveData;

		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Saving)
		FString SaveSlotName;

		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Saving)
		int HowManyLevels = 3;
	public:
		
		USaveGameSystem();
		UFUNCTION(BlueprintCallable)
    	bool SaveAllTheSelectedData(const TScriptInterface<IInteractor>& Interactor);
    
    	UFUNCTION(BlueprintCallable)
    	bool LoadAllTheSelectedData(const TScriptInterface<IInteractor>& Interactor) const;
    
    	UFUNCTION(BlueprintCallable)
    	void DeleteSaveData() const;
};
