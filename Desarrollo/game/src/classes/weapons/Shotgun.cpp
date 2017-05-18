#include "Shotgun.h"
#include "Player.h"
#include "WorldInstance.h"
#include "Scene.h"

Shotgun::Shotgun()
{
    id=eShotgun;
    m_damage = 5;
    m_ammo = 7;
    m_ammoClip = 7;
    m_bagAmmo = 32;
    m_cadence = 1.0;
}

Shotgun::~Shotgun()
{
    //dtor
}

//////////////
void Shotgun::shoot()
{
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "shotgunBullet", m_damage);
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
