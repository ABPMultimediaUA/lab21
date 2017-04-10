#include "Gun.h"
#include "Player.h"
#include "WorldInstance.h"

Gun::Gun()
{
    //ctor
    id = 0;
    this->Weapon::setAmmo(12); //12
    this->Weapon::setAmmoClip(12);
    this->Weapon::setAmmoBag(24);
    m_cadence = 0.6;
}

Gun::~Gun()
{
    //dtor
}

//////////
void Gun::shoot()
{
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "gunBullet");
    NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "gunBullet"); // Enviamos mensaje para crear projectil
}

//////////
void Gun::reload()
{
    // TODO
}
