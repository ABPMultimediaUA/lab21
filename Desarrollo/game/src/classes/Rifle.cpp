#include "Rifle.h"
#include "Player.h"
#include "WorldInstance.h"

Rifle::Rifle()
{
    //ctor
    id=2;
}

Rifle::~Rifle()
{
    //dtor
}

////////////
void Rifle::shoot()
{
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "rifleBullet");
}

////////////
void Rifle::reload()
{
    // TODO
}
