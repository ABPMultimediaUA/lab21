#include "Grenade.h"
#include "Player.h"
#include "WorldInstance.h"
#include "Scene.h"

Grenade::Grenade()
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
