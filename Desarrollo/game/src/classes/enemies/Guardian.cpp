#include "Guardian.h"
#include "Pathplanning.h"
#include "Perception.h"
#include <GuardianStates.h>
#include "BTreeHumanoid.h"

Guardian::Guardian()
{
    //set up state machine
    g_pStateMachine = new StateMachine<Guardian>(this);

    g_pStateMachine->SetCurrentState(GPatrolState::Instance());

    m_speed = 2.0;   // m/s
    m_attackPower = 30;
    m_maxHealth = 30;
    m_health = m_maxHealth;

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    m_behaviourTree = new BTreeHumanoid(this);

}

void Guardian::update()
{
    //g_pStateMachine->Update();
    Enemy::update();
    m_behaviourTree->Run();
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
    delete m_behaviourTree;
    delete g_pStateMachine;
}
