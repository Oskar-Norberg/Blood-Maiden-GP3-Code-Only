#include "StateMachine/StateMachine.h"
#include "StateMachine/States/BaseState.h"
#include "StateMachine/States/MenuState.h"

UStateMachine::UStateMachine() {}
UStateMachine::~UStateMachine() {}

void UStateMachine::Update() const
{
	M_CurrentState->UpdateState();
}

void UStateMachine::SetState(const TSubclassOf<UBaseState> NewStateClass)
{
	if (!NewStateClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to change to null state class"));
		return;
	}

	CleanUpCurrentState();

	M_CurrentState = NewObject<UBaseState>(this, *NewStateClass);
	if (M_CurrentState)
		M_CurrentState->EnterState();
	
	OnStateChange.Broadcast(M_CurrentState); //Sends out an event that tells the listener what the new state is
}

UObject* UStateMachine::GetState() const { return M_CurrentState; }

void UStateMachine::CleanUpCurrentState()
{
	if(!M_CurrentState) return;
	
	M_CurrentState->ExitState();
	UE_LOG(LogTemp, Log, TEXT("Exited state: %s"), *M_CurrentState->GetClass()->GetName());
	
	M_CurrentState = nullptr;
}

void UStateMachine::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SetState(UMenuState::StaticClass());
}