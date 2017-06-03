#ifndef WORLD_H
#define WORLD_H

#include "GraphicsEngine.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <SFML/System.hpp>

#define M_PI 3.14159265358979323846


class Player;
class EntityPhysics;

/////////////////////////////////////////////////////////
// Clase que se encarga de obtener los eventos de las
// colisiones de los objetos de box2d.
// Detecta las colisiones entre las clases derivadas de
// EntityPhysics y llama a sus eventos:
// onBeginContact y onEndContact
/////////////////////////////////////////////////////////
class ContactListener : public b2ContactListener
{
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
};


//Raycast
class RayCastCallback : public b2RayCastCallback
{
    public:

        RayCastCallback();

        float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                              const b2Vec2& normal, float32 fraction);

        bool m_hit;
        b2Vec2 m_point;
        b2Vec2 m_normal;
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

        b2Joint* createJoint(const b2JointDef *jointDef);
        void destroyJoint(b2Joint *joint);

        /// \brief Se ejecuta el step de Box2D con un ratio fijo _timeStep.
        void step();

        void clearForces();

        b2Vec2 getGravity();
        b2World* getWorld();

        float getTimeElapsed();

        Player* getMainPlayer();
        void setMainPlayer(Player* p);

        bool CheckWallsRayCast(dwe::vec2f point1, dwe::vec2f point2);

        dwe::vec3f from2Dto3D(int x2d, int y2d, dwe::vec3f rotation);

        void startDebugPhysics();
        void drawDebugPhysics(dwe::vec3f cameraPosition);
        void stopDebugPhysics();

        void setActiveDebugPhysics(bool active);

    protected:

    private:
        static WorldInstance* pinstance;

        static constexpr float   _timeStep              = 1.0/60.0;
        static constexpr uint8_t _velocityIterations    = 8;
        static constexpr uint8_t _positionIterations    = 3;

        static b2Vec2           m_gravity;
        static b2World          m_world;
        static ContactListener  m_contactListener;

        static bool m_debuggingPhysics;

        static Player* m_mainPlayer;

        static float deltaTimeAccum;
        static sf::Clock m_clock;
};

#define World WorldInstance::Instance()

#endif // WORLD_H
