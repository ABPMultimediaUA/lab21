#include "Legless.h"

Legless::Legless()
{
    //set up state machine
    l_pStateMachine = new StateMachine<Legless>(this);

    l_pStateMachine->SetCurrentState(LPatrolState::Instance());

}

void Legless::Update()
{
    l_pStateMachine->Update();
}

StateMachine<Legless>* Legless::GetFSM()const
{
    return l_pStateMachine;
}

Legless::~Legless()
{
    delete l_pStateMachine;
}
