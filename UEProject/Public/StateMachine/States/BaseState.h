#pragma once
#include "BaseState.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UEPROJECT_API UBaseState : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateMachine")
	void EnterState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateMachine")
	void UpdateState();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateMachine")
	void ExitState();
};