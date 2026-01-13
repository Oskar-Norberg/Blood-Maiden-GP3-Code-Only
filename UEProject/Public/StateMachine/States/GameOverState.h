#pragma once
#include "StateMachine/States/BaseState.h"
#include "GameOverState.generated.h"

UCLASS(Blueprintable)
class UGameOverState final : public UBaseState
{
	GENERATED_BODY()
	
public:
	virtual void EnterState_Implementation() override;
	virtual void UpdateState_Implementation() override;
	virtual void ExitState_Implementation() override;
};