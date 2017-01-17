#include "Scene.h"
#include "Projectile.h"


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

