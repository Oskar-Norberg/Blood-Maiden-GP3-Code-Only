#pragma once
#include "CoreMinimal.h"
#include "StateMachine.generated.h"

class UBaseState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChange, UBaseState*, NewState);

UCLASS(Blueprintable)
class UStateMachine final : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UBaseState> M_CurrentState = nullptr;
	
public:
	UStateMachine();
	virtual ~UStateMachine() override;

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void Update() const;

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void SetState(TSubclassOf<UBaseState> NewStateClass);

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	UObject* GetState() const;

	UPROPERTY(BlueprintAssignable, Category = "StateMachine")
	FOnStateChange OnStateChange;

private:
	void CleanUpCurrentState();

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};