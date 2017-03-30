#include "Shotgun.h"
#include "Player.h"
#include "WorldInstance.h"

Shotgun::Shotgun()
{
    //ctor
    id=1;
}

Shotgun::~Shotgun()
{
    //dtor
}

//////////////
void Shotgun::shoot()
{cout << "disparo escopeta" << endl;
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "shotgunBullet");
    NetInstance->sendBroadcast(ID_PROJECTILE_CREATE,World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "shotgunBullet"); // Enviamos mensaje para crear projectil
}

//////////////
void Shotgun::reload()
{
    // TODO
}
