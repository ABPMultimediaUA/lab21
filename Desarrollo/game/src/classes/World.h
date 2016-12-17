#ifndef WORLD_H
#define WORLD_H

#include "Scene.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class World
{
    public:
        static World* Instance();

        b2Body* createBody(b2BodyDef *bodyDef);
        void step(float deltaTime);
        void clearForces();

        b2Vec2 getGravity();
        b2World getWorld();
    protected:

    private:
        static const float  m_timeStep;
        static const int    m_velocityIterations;
        static const int    m_positionIterations;

        static b2Vec2       m_gravity;
        static b2World      m_world;
};

#define WInstance World::Instance()

#endif // WORLD_H
