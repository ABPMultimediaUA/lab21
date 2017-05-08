#include "Guardian.h"
#include "Pathplanning.h"
#include "Perception.h"

Guardian::Guardian()
{
    steps = 2000;
    //set up state machine
    g_pStateMachine = new StateMachine<Guardian>(this);

    g_pStateMachine->SetCurrentState(GPatrolState::Instance());

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

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
    steps--;
    //g_pStateMachine->Update();
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
    delete m_perception;
    delete m_pathplanning;

    delete g_pStateMachine;
}
