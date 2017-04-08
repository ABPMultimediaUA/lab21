#ifndef WORLD_H
#define WORLD_H

#include "Scene.h"
#include "EntityPhysics.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <SFML/System.hpp>

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

        /// \brief Se ejecuta el step de Box2D con un ratio fijo _timeStep.
        void step();

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

        static const float   _timeStep              = 1.0/60.0;
        static const uint8_t _velocityIterations    = 8;
        static const uint8_t _positionIterations    = 3;

        static b2Vec2           m_gravity;
        static b2World          m_world;
        static ContactListener  m_contactListener;

        static Player* m_mainPlayer;

        static float deltaTimeAccum;
        static sf::Clock m_clock;
};

#define World WorldInstance::Instance()

#endif // WORLD_H
