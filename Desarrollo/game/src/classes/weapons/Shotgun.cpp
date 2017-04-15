#include "Shotgun.h"
#include "Player.h"
#include "WorldInstance.h"
#include "Scene.h"

Shotgun::Shotgun()
{
    id=eShotgun;
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

//////////////
void Shotgun::setPut()
{
    this->setActive(false);
}

//////////////
void Shotgun::setDraw()
{
    this->setActive(true);
}
