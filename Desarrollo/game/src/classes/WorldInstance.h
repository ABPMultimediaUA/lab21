#ifndef WORLD_H
#define WORLD_H

#include "Scene.h"
#include "EntityPhysics.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

#define PLAYER_SPEED 50.0f
#define M_PI 3.14159265358979323846


class Player;

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
        EntityPhysics* bodyUserDataA = (EntityPhysics*)contact->GetFixtureA()->GetBody()->GetUserData();
        EntityPhysics* bodyUserDataB = (EntityPhysics*)contact->GetFixtureB()->GetBody()->GetUserData();

        if (bodyUserDataA)
            bodyUserDataA->onEndContact(bodyUserDataB);

        if (bodyUserDataB)
            bodyUserDataB->onEndContact(bodyUserDataA);
    }
};



////////////////////////////////////////////////////////
// El mundo
////////////////////////////////////////////////////////
class WorldInstance
{
    public:
        static WorldInstance* Instance();

        WorldInstance();
        ~WorldInstance(){};

        void Update();

        void init();

        b2Body* createBody(b2BodyDef *bodyDef);
        void destroyBody(b2Body *body);

        /// \brief Se ejecuta el step de Box2D.
        /// \details Acumula deltaTime y solo llama a step cuando ha pasado el tiempo definido en m_timeStep
        /// \param[in] deltaTime tiempo que ha pasado desde la última llamada
        void step(float deltaTime);

        void clearForces();

        b2Vec2 getGravity();
        b2World getWorld();

        float getTimeElapsed();

        Player* getMainPlayer();
        void setMainPlayer(Player* p);


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

        static Player* m_mainPlayer;

        static float deltaTimeAccum;
};

#define World WorldInstance::Instance()

#endif // WORLD_H
