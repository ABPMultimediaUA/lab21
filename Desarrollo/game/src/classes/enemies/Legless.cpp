#include "Legless.h"

Legless::Legless()
{
    steps = 2000;
    //set up state machine
    l_pStateMachine = new StateMachine<Legless>(this);

    l_pStateMachine->SetCurrentState(LPatrolState::Instance());

}

void Legless::Update()
{
    steps--;
    l_pStateMachine->Update();
}

StateMachine<Legless>* Legless::GetFSM()const
{
    return l_pStateMachine;
}

int Legless::getSteps ()
{
    return steps;
}

void Legless::setSteps (int s)
{
    steps = s;
}

void Legless::update()
{

}

void Legless::render()
{

}

Legless::~Legless()
{
    delete l_pStateMachine;
}
