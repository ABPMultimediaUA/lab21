#include "Dog.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "BTreeHumanoid.h"

Dog::Dog()
{
    //set up state machine
    d_pStateMachine = new StateMachine<Dog>(this);

    d_pStateMachine->SetCurrentState(DAsleepState::Instance());

    m_speed = 5.0;   // m/s
    m_attackPower = 20;
    m_maxHealth = 15;
    m_health = m_maxHealth;

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    m_behaviourTree = new BTreeHumanoid(this);

}

Dog::~Dog()
{
    delete d_pStateMachine;
    delete m_perception;
    delete m_pathplanning;
    delete m_behaviourTree;
}

StateMachine<Dog>* Dog::GetFSM()const
{
    return d_pStateMachine;
}

void Dog::update()
{
    //d_pStateMachine->Update();
    Enemy::update();
    m_behaviourTree->Run();
}

void Dog::render()
{

}

