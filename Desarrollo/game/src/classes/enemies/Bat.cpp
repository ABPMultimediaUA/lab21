#include "Bat.h"

Bat::Bat()
{
    //set up state machine
    b_pStateMachine = new StateMachine<Bat>(this);

    b_pStateMachine->SetCurrentState(BPatrolState::Instance());

}

StateMachine<Bat>* Bat::GetFSM()const
{
    return b_pStateMachine;
}

void Bat::update()
{
    b_pStateMachine->Update();
}

Bat::~Bat()
{
    delete b_pStateMachine;
}
