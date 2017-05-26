#include "Grenade.h"
#include "Player.h"
#include "WorldInstance.h"
#include "Scene.h"

Grenade::Grenade() :
    m_cadence(2.0)
{
    //ctor
}

Grenade::~Grenade()
{
    //dtor
}

//////////////
void Grenade::shoot()
{
    Scene::Instance()->createProjectileGrenade(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y);
}

float Grenade::getCadence()
{
    return m_cadence;
}
