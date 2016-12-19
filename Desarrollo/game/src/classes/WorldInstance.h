#ifndef WORLD_H
#define WORLD_H

#include "Scene.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>


#define PLAYER_SPEED 50.0f
#define M_PI 3.14159265358979323846
#define POS_ERROR 100 // Creado para el ajuste de coordenadas de los muros de blender/irrlicht a box2d


class WorldInstance
{
    public:
        static WorldInstance* Instance();

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

#define World WorldInstance::Instance()

#endif // WORLD_H
