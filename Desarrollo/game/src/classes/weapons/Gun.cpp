#include "Gun.h"
#include "Player.h"
#include "WorldInstance.h"

Gun::Gun()
{
    id = eGun;
    this->Weapon::setAmmo(12);
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

//////////
void Gun::setPut()
{
    this->setActive(false);
}

//////////
void Gun::setDraw()
{
    this->setActive(true);
}
