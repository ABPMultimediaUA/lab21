#include <time.h>
#include "WorldInstance.h"
#include "Player.h"

WorldInstance* WorldInstance::pinstance = 0;

b2Vec2  WorldInstance::m_gravity(0.f, 0.f);
b2World WorldInstance::m_world(WorldInstance::m_gravity);
ContactListener WorldInstance::m_contactListener;
Player* WorldInstance::m_mainPlayer = 0;


const float   WorldInstance::m_timeStep             = 1.0f / 250.0f;;
const int     WorldInstance::m_velocityIterations   = 6;
const int     WorldInstance::m_positionIterations   = 2;


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

WorldInstance::WorldInstance(){

    // Puertas

}

void WorldInstance::Update()
{

}

////////////////////
void WorldInstance::init()
{
    m_world.SetContactListener(&m_contactListener);


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

////////////////////
void WorldInstance::step(float deltaTime)
{
    m_world.Step(deltaTime * m_timeStep, m_velocityIterations, m_positionIterations);
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
    return clock();
}

//////////////////////
b2Vec2 WorldInstance::getGravity(){return(m_gravity);}

///////////////////////
b2World WorldInstance::getWorld(){return(m_world);}

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
