#include "Gun.h"
#include "Player.h"
#include "WorldInstance.h"
#include "Scene.h"

Gun::Gun()
{
    id = eGun;
    m_damage = 3;
    m_ammo = 12;
    m_ammoClip = 12;
    m_bagAmmo = 24;
    m_cadence = 0.6;
}

Gun::~Gun()
{
    //dtor
}

//////////
void Gun::shoot()
{
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "gunBullet", m_damage);
    NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, RakNet::RakString("gunBullet")); // Enviamos mensaje para crear projectil
}

//////////
void Gun::reload()
{
    // TODO
}

//////////
void Gun::setPut()
{
    setActive(false);
}

//////////
void Gun::setDraw()
{
    setActive(true);
}
