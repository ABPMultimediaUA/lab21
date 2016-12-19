#include "WorldInstance.h"

b2Vec2  WorldInstance::m_gravity(0.f, 0.f);
b2World WorldInstance::m_world(WorldInstance::m_gravity);

const float   WorldInstance::m_timeStep             = 1.0f / 250.0f;;
const int     WorldInstance::m_velocityIterations   = 6;
const int     WorldInstance::m_positionIterations   = 2;


//////////////
WorldInstance* WorldInstance::Instance()
{
    // Devuelvo singleton

    static WorldInstance instance;
    return &instance;
}

///////////////////////
b2Body* WorldInstance::createBody(b2BodyDef *bodyDef)
{
    return m_world.CreateBody(bodyDef);
}

////////////////////
void WorldInstance::step(float deltaTime)
{
    m_world.Step(deltaTime * m_timeStep, m_velocityIterations, m_positionIterations);
}

////////////////////
void WorldInstance::clearForces()
{
    m_world.ClearForces();
}




//////////////////////
b2Vec2 WorldInstance::getGravity(){return(m_gravity);}

///////////////////////
b2World WorldInstance::getWorld(){return(m_world);}
