#include "Scene.h"
#include "Projectile.h"
#include "SpeedBoost.h"


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
void Scene::updateSpeedBoosts()
{
    unsigned int i=0;
    while(i<m_speedBoosts.size())
    {
        m_speedBoosts[i]->update();

        i++;
    }
}

////////////
void Scene::createSpeedBoost(int i, Player* p, float px, float py, float pz)
{
    m_speedBoosts.push_back(GEInstance->createSpeedBoost(i, p, px, py, pz));
}
