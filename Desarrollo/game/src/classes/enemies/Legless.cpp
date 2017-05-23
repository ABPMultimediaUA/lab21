#include "Legless.h"
#include "LeglessStates.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "BTreeHumanoid.h"

Legless::Legless()
{
    //set up state machine
    l_pStateMachine = new StateMachine<Legless>(this);

    l_pStateMachine->SetCurrentState(LPatrolState::Instance());

    m_speed = 2.0;   // m/s
    m_attackPower = 20;

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    m_behaviourTree = new BTreeHumanoid(this);

    targetPosition = dwe::vec2f(-550,-340);

}

StateMachine<Legless>* Legless::GetFSM()const
{
    return l_pStateMachine;
}

void Legless::update()
{
    //l_pStateMachine->Update();
    Enemy::update();
    m_behaviourTree->Run();
}

Legless::~Legless()
{
    delete m_perception;
    delete m_pathplanning;
    delete m_behaviourTree;
    delete l_pStateMachine;
}
