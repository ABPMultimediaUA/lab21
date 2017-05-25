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

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    m_behaviourTree = new BTreeHumanoid(this);



    targetPosition = dwe::vec2f(470,370);
    m_pathplanning->SetNext(targetPosition);
    SetPatrolPoints(dwe::vec2f(380,640), dwe::vec2f(-720,0));
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
