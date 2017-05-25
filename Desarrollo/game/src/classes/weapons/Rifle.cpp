#include "Rifle.h"
#include "Player.h"
#include "WorldInstance.h"
#include "Scene.h"

Rifle::Rifle()
{
    id=eRifle;
    m_damage = 2;
    m_ammo = 30;
    m_ammoClip = 30;
    m_bagAmmo = 90;
    m_cadence = 0.08;
}

Rifle::~Rifle()
{
    //dtor
}

////////////
void Rifle::shoot()
{
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "rifleBullet", m_damage);
    NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, World->getMainPlayer()->getPosition(),World->getMainPlayer()->getRotation().y, RakNet::RakString("rifleBullet")); // Enviamos mensaje para crear projectil
}

////////////
void Rifle::reload()
{
    // TODO
}

////////////
void Rifle::setPut()
{
    setActive(false);
}

////////////
void Rifle::setDraw()
{
    setActive(true);
}
