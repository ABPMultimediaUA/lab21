#include <time.h>
#include "WorldInstance.h"
#include "EntityPhysics.h"
#include "Player.h"

#ifdef LAB21_DEBUG
#include "DebugPhysicsDraw.h"
#endif // LAB21_DEBUG

void ContactListener::BeginContact(b2Contact* contact)
{
    EntityPhysics* bodyUserDataA = (EntityPhysics*)contact->GetFixtureA()->GetBody()->GetUserData();
    EntityPhysics* bodyUserDataB = (EntityPhysics*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyUserDataA)
        bodyUserDataA->onBeginContact(bodyUserDataB);

    if (bodyUserDataB)
        bodyUserDataB->onBeginContact(bodyUserDataA);
}

void ContactListener::EndContact(b2Contact* contact)
{
    EntityPhysics* bodyUserDataA = (EntityPhysics*)contact->GetFixtureA()->GetBody()->GetUserData();
    EntityPhysics* bodyUserDataB = (EntityPhysics*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyUserDataA)
        bodyUserDataA->onEndContact(bodyUserDataB);

    if (bodyUserDataB)
        bodyUserDataB->onEndContact(bodyUserDataA);
}

RayCastCallback::RayCastCallback()
{
    m_hit = false;
}

float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                     const b2Vec2& normal, float32 fraction)
{
    EntityPhysics* userData = (EntityPhysics*)fixture->GetBody()->GetUserData();
    if (userData)
    {
        EntityPhysics::EPClassID clase = userData->getClassID();
        if (clase == EntityPhysics::wall_id)
        {
            m_hit = true;
            m_point = point;
            m_normal = normal;
            return 0.0f;
        }
    }
    return -1.0f;
}


WorldInstance* WorldInstance::pinstance = 0;

b2Vec2  WorldInstance::m_gravity(0.f, 0.f);
b2World WorldInstance::m_world(WorldInstance::m_gravity);
ContactListener WorldInstance::m_contactListener;
Player* WorldInstance::m_mainPlayer = 0;
float WorldInstance::deltaTimeAccum = 0;
sf::Clock WorldInstance::m_clock;

bool WorldInstance::m_debuggingPhysics;

//////////////
WorldInstance* WorldInstance::Instance()
{
    // Devuelvo singleton
    if(pinstance==0)
    {
        pinstance = new WorldInstance;
        pinstance->init();
    }
    return pinstance;
}

WorldInstance::WorldInstance()
{
}

void WorldInstance::Update()
{

}

////////////////////
void WorldInstance::init()
{
    m_debuggingPhysics = false;
    m_world.SetContactListener(&m_contactListener);
    deltaTimeAccum = 0.0;
    m_clock.restart();
}

///////////////////////
b2Body* WorldInstance::createBody(b2BodyDef *bodyDef)
{
    return m_world.CreateBody(bodyDef);
}

///////////////////////
void WorldInstance::destroyBody(b2Body *body)
{
    return m_world.DestroyBody(body);
}

///////////////////////
b2Joint* WorldInstance::createJoint(const b2JointDef *jointDef)
{
    return m_world.CreateJoint(jointDef);
}

///////////////////////
void WorldInstance::destroyJoint(b2Joint *joint)
{
    return m_world.DestroyJoint(joint);
}

////////////////////
void WorldInstance::step()
{
    m_world.Step(_timeStep, _velocityIterations, _positionIterations);
}

////////////////////
void WorldInstance::clearForces()
{
    m_world.ClearForces();
}


//////////////////////////
dwe::vec3f WorldInstance::from2Dto3D(int x2d, int y2d, dwe::vec3f rotation)
{
    int centerX = GEInstance->get_screenWidth()/2;
    int centerY = GEInstance->get_screenHeight()/2;

	dwe::vec3f v(x2d - centerX, y2d - centerY,0);
    dwe::vec3f u(1,0,0);

	float numerador     = (u.x*v.x) + (u.y*v.y);
	float denominador   = sqrt( pow(u.x,2) + pow(u.y,2) ) * sqrt( pow(v.x,2) + pow(v.y,2) );
	float angulo        = acos(numerador/denominador) * (180/M_PI);

	if(y2d>centerY)
        rotation.y = -angulo;
	else
        rotation.y = angulo;

    return(rotation);
}

/////////////////////
float WorldInstance::getTimeElapsed()
{
    return m_clock.getElapsedTime().asSeconds();
}

//////////////////////
b2Vec2 WorldInstance::getGravity(){return(m_gravity);}

///////////////////////
b2World* WorldInstance::getWorld(){return(&m_world);}

///////////////////////
void WorldInstance::setMainPlayer(Player* p) { m_mainPlayer = p; }
Player* WorldInstance::getMainPlayer()
{
    if (m_mainPlayer == 0)
    {
        cout << "\nERROR: No se ha asignado el mainPlayer al mundo\n";
        return 0;
    }
    else
        return m_mainPlayer;
}

bool WorldInstance::CheckWallsRayCast(dwe::vec2f point1, dwe::vec2f point2)
{
    RayCastCallback callback;
    m_world.RayCast(&callback, b2Vec2(point1.x, point1.y), b2Vec2(point2.x, point2.y));
    if(callback.m_hit)
    {
        return true;
    }

    return false;
}

////////////////////
void WorldInstance::startDebugPhysics()
{
#ifdef LAB21_DEBUG
    g_debugDraw.Create();
    m_world.SetDebugDraw(&g_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_centerOfMassBit;
	g_debugDraw.SetFlags(flags);
#endif // LAB21_DEBUG
}

////////////////////
void WorldInstance::stopDebugPhysics()
{
#ifdef LAB21_DEBUG
    g_debugDraw.Destroy();
#endif // LAB21_DEBUG
}

////////////////////
void WorldInstance::drawDebugPhysics(dwe::vec3f cameraPosition)
{
#ifdef LAB21_DEBUG
    if (m_debuggingPhysics)
    {
        GEInstance->pop();
        g_camera.m_center = b2Vec2(cameraPosition.x*0.035, -cameraPosition.z*0.035);
        m_world.DrawDebugData();
        g_debugDraw.Flush();
        GEInstance->push();
    }
#endif // LAB21_DEBUG
}

////////////////////
void WorldInstance::setActiveDebugPhysics(bool active)
{
    m_debuggingPhysics = active;
}
