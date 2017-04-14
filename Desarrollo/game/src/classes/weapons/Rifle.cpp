#include "Rifle.h"
#include "Player.h"
#include "WorldInstance.h"

Rifle::Rifle()
{
    id=eRifle;
    this->Weapon::setAmmo(30);
    this->Weapon::setAmmoClip(30);
    this->Weapon::setAmmoBag(90);
    m_cadence = 0.08;
}

Rifle::~Rifle()
{
    //dtor
}

////////////
void Rifle::shoot()
{
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "rifleBullet");
    NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, World->getMainPlayer()->getPosition(),World->getMainPlayer()->getRotation().y, "rifleBullet"); // Enviamos mensaje para crear projectil
}

////////////
void Rifle::reload()
{
    // TODO
}

////////////
void Rifle::setPut()
{
    this->setActive(false);
}

////////////
void Rifle::setDraw()
{
    this->setActive(true);
}
