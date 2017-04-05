#include "Bat.h"

Bat::Bat()
{
    steps = 2000;
    //set up state machine
    b_pStateMachine = new StateMachine<Bat>(this);

    b_pStateMachine->SetCurrentState(BPatrolState::Instance());

}

void Bat::Update()
{
    steps--;
    b_pStateMachine->Update();
}

StateMachine<Bat>* Bat::GetFSM()const
{
    return b_pStateMachine;
}

int Bat::getSteps ()
{
    return steps;
}

void Bat::setSteps (int s)
{
    steps = s;
}

void Bat::update()
{

}

void Bat::render()
{

}

Bat::~Bat()
{
    delete b_pStateMachine;
}
