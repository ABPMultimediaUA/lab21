#include "Shotgun.h"
#include "Player.h"
#include "WorldInstance.h"

Shotgun::Shotgun()
{
    //ctor
    id=1;
    this->Weapon::setAmmo(7);
    this->Weapon::setAmmoClip(7);
    this->Weapon::setAmmoBag(32);
    m_cadence = 1.0;
}

Shotgun::~Shotgun()
{
    //dtor
}

//////////////
void Shotgun::shoot()
{
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "shotgunBullet");
    NetInstance->sendBroadcast(ID_PROJECTILE_CREATE,World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "shotgunBullet"); // Enviamos mensaje para crear projectil
}

//////////////
void Shotgun::reload()
{
    // TODO
}
