#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerDeathComponent.generated.h"

class UEntityStats;

UCLASS(ClassGroup=(Player), meta=(BlueprintSpawnableComponent), Blueprintable)
class UEPROJECT_API UPlayerDeathComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorComponent> PlayerEntityStatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EventBindDelay = 0.5f;

	UPROPERTY()
	bool WeakState = false;
	
	UPlayerDeathComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnDeath();

	UFUNCTION(BlueprintCallable)
	void BindDeathEvent();
};