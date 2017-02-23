#include "Guardian.h"

Guardian::Guardian()
{
    //set up state machine
    g_pStateMachine = new StateMachine<Guardian>(this);

    g_pStateMachine->SetCurrentState(GPatrolState::Instance());

}

void Guardian::Update()
{
    g_pStateMachine->Update();
}

StateMachine<Guardian>* Guardian::GetFSM()const
{
    return g_pStateMachine;
}

Guardian::~Guardian()
{
    delete g_pStateMachine;
}
