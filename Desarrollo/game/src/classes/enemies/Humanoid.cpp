#include "Humanoid.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "TriggerVision.h"
#include "Scene.h"
#include "BTreeHumanoid.h"

Humanoid::Humanoid()
{
    m_speed = 4.0;   // m/s
    m_attackPower = 20;
    m_maxHealth = 20;
    m_health = m_maxHealth;

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    m_behaviourTree = new BTreeHumanoid(this);

}

void Humanoid::update()
{
    Enemy::update();
    m_behaviourTree->Run();
}


Humanoid::~Humanoid()
{
    delete m_perception;
    delete m_pathplanning;
    delete m_behaviourTree;
}
