#include "World.h"

b2Vec2  World::m_gravity(0.f, 0.f);
b2World World::m_world(World::m_gravity);

const float   World::m_timeStep             = 1.0f / 250.0f;;
const int     World::m_velocityIterations   = 6;
const int     World::m_positionIterations   = 2;


//////////////
World* World::Instance()
{
    // Devuelvo singleton

    static World instance;
    return &instance;
}

//////////////
b2Body* World::createBody(b2BodyDef *bodyDef)
{
    return m_world.CreateBody(bodyDef);
}

////////////
void World::step(float deltaTime)
{
    m_world.Step(deltaTime * m_timeStep, m_velocityIterations, m_positionIterations);
}

////////////
void World::clearForces()
{
    m_world.ClearForces();
}




////////////
b2Vec2 World::getGravity(){return(m_gravity);}

////////////
b2World World::getWorld(){return(m_world);}
