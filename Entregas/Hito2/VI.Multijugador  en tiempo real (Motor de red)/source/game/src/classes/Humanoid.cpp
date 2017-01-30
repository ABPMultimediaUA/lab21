#include "Humanoid.h"

Humanoid::Humanoid()
{
    steps = 19;
    m_speed = 0.1;

    //set up state machine
    h_pStateMachine = new StateMachine<Humanoid>(this);

    h_pStateMachine->SetCurrentState(HPatrolState::Instance());

}

void Humanoid::Update()
{
    steps--;
    h_pStateMachine->Update();
}

StateMachine<Humanoid>* Humanoid::GetFSM()const
{
    return h_pStateMachine;
}

int Humanoid::getSteps ()
{
    return steps;
}

Humanoid::~Humanoid()
{
    delete h_pStateMachine;
}
