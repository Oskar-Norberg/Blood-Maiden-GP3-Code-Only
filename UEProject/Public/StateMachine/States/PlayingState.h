#pragma once
#include "StateMachine/States/BaseState.h"
#include "PlayingState.generated.h"

UCLASS(Blueprintable)
class UPlayingState final : public UBaseState
{
	GENERATED_BODY()
	
public:
	virtual void EnterState_Implementation() override;
	virtual void UpdateState_Implementation() override;
	virtual void ExitState_Implementation() override;
};