#include "Mother.h"

Mother::Mother()
{

    TimeBetweenCreations = 0;
    //set up state machine
    m_pStateMachine = new StateMachine<Mother>(this);

    m_pStateMachine->SetCurrentState(StillState::Instance());

}

void Mother::Update()
{
    TimeBetweenCreations ++;
    m_pStateMachine->Update();
}

StateMachine<Mother>* Mother::GetFSM()const
{
    return m_pStateMachine;
}

void Mother::setTimeBetweenCreations (int n)
{
    TimeBetweenCreations = n;
}

int Mother::getTimeBetweenCreations()
{
    return TimeBetweenCreations;
}

Mother::~Mother()
{
    delete m_pStateMachine;
}
