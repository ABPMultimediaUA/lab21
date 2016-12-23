#ifndef WORLD_H
#define WORLD_H

#include "Scene.h"
#include "EntityPhysics.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>


#define PLAYER_SPEED 50.0f
#define M_PI 3.14159265358979323846
#define POS_ERROR 100 // Creado para el ajuste de coordenadas de los muros de blender/irrlicht a box2d

#define CLASS_NO_ID             0
#define CLASS_PLAYER_ID         1
#define CLASS_PROJECTILE_ID     2
#define CLASS_WALL_ID           3

#define SCREEN_CENTER_X 400
#define SCREEN_CENTER_Y 300

/////////////////////////////////////////////////////////
// Clase que se encarga de obtener los eventos de las
// colisiones de los objetos de box2d.
// Detecta las colisiones entre las clases derivadas de
// EntityPhysics y llama a sus eventos:
// onBeginContact y onEndContact
/////////////////////////////////////////////////////////
class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {
        EntityPhysics* bodyUserDataA = (EntityPhysics*)contact->GetFixtureA()->GetBody()->GetUserData();
        EntityPhysics* bodyUserDataB = (EntityPhysics*)contact->GetFixtureB()->GetBody()->GetUserData();

        if (bodyUserDataA)
            bodyUserDataA->onBeginContact(bodyUserDataB);

        if (bodyUserDataB)
            bodyUserDataB->onBeginContact(bodyUserDataA);
    }

    void EndContact(b2Contact* contact)
    {
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<EntityPhysics*>(bodyUserData)->onEndContact();

        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<EntityPhysics*>(bodyUserData)->onEndContact();
    }
};




class WorldInstance
{
    public:
        static WorldInstance* Instance();

        void init();

        b2Body* createBody(b2BodyDef *bodyDef);
        void destroyBody(b2Body *body);
        void step(float deltaTime);
        void clearForces();

        b2Vec2 getGravity();
        b2World getWorld();

        dwe::vec3f from2Dto3D(int x2d, int y2d, dwe::vec3f rotation);

    protected:

    private:
        static WorldInstance* pinstance;

        static const float  m_timeStep;
        static const int    m_velocityIterations;
        static const int    m_positionIterations;

        static b2Vec2           m_gravity;
        static b2World          m_world;
        static ContactListener  m_contactListener;
};

#define World WorldInstance::Instance()

#endif // WORLD_H
