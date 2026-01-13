#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelLoadingTrigger.generated.h"

UCLASS(Blueprintable)
class UEPROJECT_API ALevelLoadingTrigger : public AActor
{
	GENERATED_BODY()

public:
	ALevelLoadingTrigger();

	/** The name of the level you want to load */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FName LevelName;

	/** The time it should take for the screen to fade before loading the specified level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float FadeDuration = 1.0f;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();
	
	virtual void Tick(float DeltaTime) override;
};
