#include "Bat.h"

Bat::Bat()
{
    //set up state machine
    b_pStateMachine = new StateMachine<Bat>(this);

    b_pStateMachine->SetCurrentState(BPatrolState::Instance());

}

void Bat::Update()
{
    b_pStateMachine->Update();
}

StateMachine<Bat>* Bat::GetFSM()const
{
    return b_pStateMachine;
}

Bat::~Bat()
{
    delete b_pStateMachine;
}
