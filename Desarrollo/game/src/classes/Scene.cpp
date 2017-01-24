#include "Scene.h"
#include "Projectile.h"
#include "SpeedBoost.h"
#include "Medkit.h"
#include "Consumable.h"
#include "AmmoGun.h"
#include "CShotgun.h"
#include "CRifle.h"

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    //dtor
}

////////////
void Scene::updateProjectiles()
{
    unsigned int i=0;
    while(i<m_projectiles.size())
    {
        m_projectiles[i]->update();
        if (m_projectiles[i]->getCollides())
        {
            delete m_projectiles[i];
            m_projectiles.erase(m_projectiles.begin()+i);
        }
        else
            i++;
    }
}

////////////
void Scene::deleteProjectile(unsigned int i)
{
    if (i<m_projectiles.size())
    {
        delete m_projectiles[i];
        m_projectiles.erase(m_projectiles.begin()+i);
    }
}


////////////
void Scene::createProjectile(dwe::vec3f origin, float angle)
{
    m_projectiles.push_back(GEInstance->createProjectile(origin, angle));
}

////////////
void Scene::updateConsumables(Player* mainPlayer)
{
    unsigned int i=0;
    while(i<m_consumables.size())
    {
        m_consumables[i]->update(mainPlayer);
        if (m_consumables[i]->getIsTaken())
        {
            delete m_consumables[i];
            m_consumables.erase(m_consumables.begin()+i);
        }
        else
            i++;
    }
}

void Scene::updatePlayerWeapons(Player* mainplayer, Firearm** weapons)
{
    if  (mainplayer->getCurrentWeaponType() == eGun)
    {
        weapons[0]->setPosition(dwe::vec3f(mainplayer->getPosition().x - 20, 20, mainplayer->getPosition().z));

    }
    else if (mainplayer->getCurrentWeaponType() == eShotgun)
    {
        weapons[1]->setPosition(dwe::vec3f(mainplayer->getPosition().x - 20, 20, mainplayer->getPosition().z));
    }
    else if (mainplayer->getCurrentWeaponType() == eRifle)
    {
        weapons[2]->setPosition(dwe::vec3f(mainplayer->getPosition().x - 20, 20, mainplayer->getPosition().z));
    }
}

////////////
void Scene::createSpeedBoost(float px, float py, float pz)
{
    m_consumables.push_back(GEInstance->createSpeedBoost(px, py, pz));

    //GEInstance->createSpeedBoost(px, py, pz);

}

////////////
void Scene::createMedkit(float px, float py, float pz)
{
    m_consumables.push_back(GEInstance->createMedkit(px, py, pz));
    //GEInstance->createMedkit(px, py, pz);
}

////////////
void Scene::createCShotgun(float px, float py, float pz)
{
    m_consumables.push_back(GEInstance->createCShotgun(px, py, pz));
    //GEInstance->createCShotgun(px, py, pz);
}

////////////
void Scene::createCRifle(float px, float py, float pz)
{
    m_consumables.push_back(GEInstance->createCRifle(px, py, pz));
    //GEInstance->createCShotgun(px, py, pz);
}

////////////
void Scene::createAmmoGun(float px, float py, float pz)
{
    m_consumables.push_back(GEInstance->createAmmoGun(px, py, pz));
    //GEInstance->createAmmoGun(px, py, pz);
}

////////////
Gun* Scene::createGun(float px, float py, float pz)
{
    return GEInstance->createGun(px, py, pz);
}

////////////
Shotgun* Scene::createShotgun(float px, float py, float pz)
{
    GEInstance->createShotgun(px, py, pz);
}

////////////
Rifle* Scene::createRifle(float px, float py, float pz)
{
    GEInstance->createRifle(px, py, pz);
}

