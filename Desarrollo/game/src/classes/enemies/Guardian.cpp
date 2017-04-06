#include "Guardian.h"

Guardian::Guardian()
{
    steps = 2000;
    //set up state machine
    g_pStateMachine = new StateMachine<Guardian>(this);

    g_pStateMachine->SetCurrentState(GPatrolState::Instance());

}

void Guardian::Update()
{
    steps--;
    g_pStateMachine->Update();
}

int Guardian::getSteps ()
{
    return steps;
}

void Guardian::setSteps (int s)
{
    steps = s;
}

void Guardian::update()
{

}

void Guardian::render()
{

}

StateMachine<Guardian>* Guardian::GetFSM()const
{
    return g_pStateMachine;
}

Guardian::~Guardian()
{
    delete g_pStateMachine;
}
