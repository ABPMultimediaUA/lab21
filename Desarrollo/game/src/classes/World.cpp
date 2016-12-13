#include "World.h"
/*
World::World()
{
    //ctor
}

World::~World()
{
    //dtor
}
*/

void World::initializePhysicsWorld()
{
    b2Vec2 m_gravity(0.0f, 0.0f);
    b2World m_world(m_gravity);
//    setGravity(0.0f, 0.0f);
//    setWorld(m_gravity);
}

////////////
b2Vec2 World::getGravity(){return(m_gravity);}

////////////
b2World World::getWorld(){return(m_world);}
