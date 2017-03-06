#include "Scene.h"
#include "Projectile.h"
#include "SpeedBoost.h"
#include "Medkit.h"
#include "Consumable.h"


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

