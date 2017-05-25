#include "Bat.h"
#include <BatStates.h>
#include "Pathplanning.h"
#include "Perception.h"
#include "BTreeHumanoid.h"

Bat::Bat()
{
    //set up state machine
    b_pStateMachine = new StateMachine<Bat>(this);

    b_pStateMachine->SetCurrentState(BPatrolState::Instance());

    m_speed = 3.0;   // m/s
    m_attackPower = 10;
    m_maxHealth = 10;
    m_health = m_maxHealth;

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    m_behaviourTree = new BTreeHumanoid(this);

}

StateMachine<Bat>* Bat::GetFSM()const
{
    return b_pStateMachine;
}

void Bat::update()
{
    Enemy::update();
    m_behaviourTree->Run();
}

Bat::~Bat()
{
    delete m_perception;
    delete m_pathplanning;
    delete b_pStateMachine;
    delete m_behaviourTree;
}
