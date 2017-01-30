#include "Guardian.h"

Guardian::Guardian()
{
    steps = 19;
    //set up state machine
    g_pStateMachine = new StateMachine<Guardian>(this);

    g_pStateMachine->SetCurrentState(GPatrolState::Instance());

}

void Guardian::Update()
{
    steps-=2;
    g_pStateMachine->Update();
}

StateMachine<Guardian>* Guardian::GetFSM()const
{
    return g_pStateMachine;
}

int Guardian::getSteps ()
{
    return steps;
}

Guardian::~Guardian()
{
    delete g_pStateMachine;
}
