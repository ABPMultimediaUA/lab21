#include "Humanoid.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "BTreeHumanoid.h"

Humanoid::Humanoid()
{
    m_speed = 2.0;   // m/s

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    m_behaviourTree = new BTreeHumanoid(this);

    targetPosition = dwe::vec2f(-200,200);
}

void Humanoid::update()
{
    m_behaviourTree->Run();
}


Humanoid::~Humanoid()
{
    delete m_perception;
    delete m_pathplanning;
}
