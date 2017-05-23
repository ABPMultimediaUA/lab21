#include "Bat.h"
#include <BatStates.h>
#include "Pathplanning.h"
#include "Perception.h"

Bat::Bat()
{
    //set up state machine
    b_pStateMachine = new StateMachine<Bat>(this);

    b_pStateMachine->SetCurrentState(BPatrolState::Instance());

    m_speed = 2.0;   // m/s
    m_attackPower = 20;

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    targetPosition = dwe::vec2f(-330,420);

}

StateMachine<Bat>* Bat::GetFSM()const
{
    return b_pStateMachine;
}

void Bat::update()
{
    Enemy::update();
    b_pStateMachine->Update();
}

Bat::~Bat()
{
    delete m_perception;
    delete m_pathplanning;
    delete b_pStateMachine;
}
