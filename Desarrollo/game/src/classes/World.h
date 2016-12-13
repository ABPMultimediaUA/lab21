#ifndef WORLD_H
#define WORLD_H

#include "Scene.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class World
{
    public:
        //World();
        //virtual ~World();

        void initializePhysicsWorld();
        b2Vec2 getGravity();
        void setGravity(float32 a, float32 b);
        b2World getWorld();
        void setWorld(b2Vec2 v);

    protected:

    private:
        b2Vec2 m_gravity;
        b2World m_world;
};

#endif // WORLD_H
