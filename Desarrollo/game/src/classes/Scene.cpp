#include "Scene.h"
#include "WorldInstance.h"
#include "Projectile.h"
#include "SpeedBoost.h"
#include "Medkit.h"
#include "Consumable.h"
#include "AmmoGun.h"
#include "CShotgun.h"
#include "CRifle.h"

Scene* Scene::Instance()
{
  static Scene instance;

  return &instance;
}

Scene::Scene()
{
    //ctor

}

void Scene::Init()
{
        entities[0]=GEInstance->createDoor(0, true, 43.5, 0, 135.9);
    entities[1]=GEInstance->createDoor(3, false, 170, 0, 0); // false
    sector[0]=entities[1];


    // Generadores
    entities[2]=GEInstance->createGenerator(0, false, -50, 0, -50); // false
    ((Generator*)entities[2])->setSector(sector, 1);

    // Llaves
    MagnetKey *llave=GEInstance->createMagnetKey(0, 50, 0, 350);
    llaveCogida=false;


    gun = createGun(0,0,0); // Creo el arma inicial del player

    // Creación de jugador

    mainPlayer = GEInstance->createMainPlayer(gun);
    mainPlayer->setPosition(dwe::vec3f(140-((NetInstance->getParticipantOrder()-1)*30),24,-80));
    mainPlayer->setLife(100);
    World->setMainPlayer(mainPlayer);
    cout << "Barra de vida: " << mainPlayer->getLife() << endl;
}

Scene::~Scene()
{
    //dtor
}

void Scene::Update()
{
    for(int cont=0; cont<NUM_ENTITIES; cont++)
        entities[cont]->update();
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

