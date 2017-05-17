#include "Scene.h"
#include "WorldInstance.h"
#include "Projectile.h"
#include "ProjectileGrenade.h"
#include "SpeedBoost.h"
#include "Medkit.h"
#include "Consumable.h"
#include "AmmoGun.h"
#include "CShotgun.h"
#include "CRifle.h"
#include "MagnetKey.h"
#include "Game.h"
#include "GSDead.h"
#include "NavGraphNode.h"
#include "NavGraphEdge.h"
#include "AudioEngine.h"
#include "TriggerSound.h"

///////////////////////////////
Scene* Scene::Instance()
{
  static Scene instance;

  return &instance;
}

Scene::Scene() : navGraph(false)
{
    //ctor
}
///////////////////////////////
void Scene::Init()
{
    m_timeLastEnemyActive   = 0;
    m_timeEnemyActive       = 5.0;  // En segundos
    m_posMother             = dwe::vec3f(0,62.0,-1617.0);


    ///////////////////////////////////
    if (NetInstance->isMultiplayer())
    {
        if (NetInstance->isServer()){
            GEInstance->addMessageLine("Pulsa Intro cuando esten todos los jugadores");
            cout<<"Pulsa Intro cuando esten todos los jugadores"<<endl;
        }else{
            GEInstance->addMessageLine("Esperando a que el servidor de la partida inicie el juego");
        }
        // En startGame solo se inicia si es el servidor
        while (!NetInstance->getGameStarted() && GEInstance->isRunning())
        {

            //GEInstance->draw(); // Si se dibuja la escena peta

            NetInstance->update();
            if (GEInstance->receiver.isKeyDown(KEY_INIT_GAME))
                NetInstance->startGame();
        }
    }
    GEInstance->addMessageLine("Partida iniciada");

    /////////////// Waypoints ///////////////////////
    NavGraphNode node0(0, dwe::vec2f(-200, 200));
    navGraph.addNode(node0);


    // MEDKITS
    //createMedkit(-300, 10, 200);

    // SPEEDBOOST
    createSpeedBoost(-300, 10, 200);

    // LLAVES
    createMagnetKey(0, 105, 0, 1345);
    createMagnetKey(1, 785, 0, 1045);
    createMagnetKey(2, 255, 0, 505);


    // Creación de jugador
    mainPlayer = GEInstance->createMainPlayer();
    //TODO he puesto posicion para pruebas mainPlayer->setPosition(dwe::vec3f(-1205-((NetInstance->getParticipantOrder()-1)*30),24,1150));
                mainPlayer->setPosition(dwe::vec3f(140-((NetInstance->getParticipantOrder()-1)*30),24,80));
    World->setMainPlayer(mainPlayer);

    mainPlayer->addWeapon(eGun);  // Por defecto tiene la pistola

    createEnemies();

    GEInstance->createCamera();
}

void Scene::createEnemies()
{
    m_numEnemies = m_numActiveEnemies = 11;
    m_enemies = new TEnemy[m_numEnemies];
    m_enemies[ 0].enemy = GEInstance->createEnemyHumanoid(-200,24,200);
    /*m_enemies[ 1].enemy = GEInstance->createEnemyDog(530,24,390);
    m_enemies[ 2].enemy = GEInstance->createEnemyBat(475,24,90);
    m_enemies[ 3].enemy = GEInstance->createEnemyGuardian(-310,24,100);
    m_enemies[ 4].enemy = GEInstance->createEnemyLegless(-630,24,410);
    m_enemies[ 5].enemy = GEInstance->createEnemyHumanoid(300,24,1150);
    m_enemies[ 6].enemy = GEInstance->createEnemyHumanoid(-300,24,570);
    m_enemies[ 7].enemy = GEInstance->createEnemyHumanoid(1470,24,330);
    m_enemies[ 8].enemy = GEInstance->createEnemyHumanoid(1350,24,180);
    m_enemies[ 9].enemy = GEInstance->createEnemyHumanoid(1860,24,130);
    m_enemies[10].enemy = GEInstance->createEnemyHumanoid(1970,24,230);*/

    GEInstance->createEnemyMother(m_posMother.x, m_posMother.y, m_posMother.z);

}

void Scene::deleteEnemies()
{
    for (uint8_t i=0; i<m_numEnemies; i++)
        delete m_enemies[i].enemy;
    delete[] m_enemies;
    m_enemies = 0;
}

///////////////////////////////
void Scene::Destroy(){
    delete mainPlayer;
    mainPlayer=0;

    delete gun;
    delete shotgun;
    delete rifle;

    deleteEnemies();

    delete enemyLegless;

    while(m_projectiles.size()>0){
        m_projectiles.pop_back();
    }
    while(m_projectilesGrenades.size()>0){
        m_projectilesGrenades.pop_back();
    }

    while(m_consumables.size()>0){
        m_consumables.pop_back();
    }

    delete joint_try;
    delete bjoint;

    m_triggerSystem.Destroy();
}

///////////////////////////////
Scene::~Scene() { if(mainPlayer) Destroy(); }

NavigationGraph& Scene::getNavGraph()
{
    return navGraph;
}

TriggerSystem& Scene::getTriggerSystem()
{
    return m_triggerSystem;
}

int Scene::getNumberEnemies()
{
    return m_numActiveEnemies;
}

void Scene::activeEnemy(uint8_t i)
{
    if (!m_enemies[i].active)
    {
        m_enemies[i].enemy->activeEnemy(m_posMother);
        m_enemies[i].active = true;
        m_numActiveEnemies++;
        m_timeLastEnemyActive = World->getTimeElapsed();
    }
}

void Scene::deactiveEnemy(uint8_t i)
{
    if (m_enemies[i].active)
    {
        m_enemies[i].enemy->deactiveEnemy();
        m_enemies[i].active = false;

        // Si estaban todos los enemigos activos, reinicio contador
        if (m_numEnemies == m_numActiveEnemies)
            m_timeLastEnemyActive = World->getTimeElapsed();

        m_numActiveEnemies--;
    }
}

void Scene::updateEnemies()
{
    m_moreEnemiesX = 0;
    m_moreEnemiesZ = 0;
    for(uint8_t i=0; i<m_numEnemies; i++)
    {
        if (!m_enemies[i].enemy)
            continue;

        if (!m_enemies[i].active)
        {
            //Enemigo inactivo
            if (World->getTimeElapsed() - m_timeLastEnemyActive > m_timeEnemyActive)
            {
                // Si ha pasado suficiente tiempo, lo activamos
                activeEnemy(i);
            }
        }
        else
        {
            //Enemigo activo
            // Borrado de enemigos (desactivacion)
            if (m_enemies[i].enemy->getHealth()<=0)
            {
                deactiveEnemy(i);
            }
            else
            {
                // Actualización de enemigos
                m_enemies[i].enemy->update();

                // Parametros para la camara inteligente
                int playerX = mainPlayer->getPosition().x;
                int playerZ = mainPlayer->getPosition().z;
                int enemyX  = m_enemies[i].enemy->getPosition().x;
                int enemyZ  = m_enemies[i].enemy->getPosition().z;
                int d2pX    = abs(playerX - enemyX);  //distance to player
                int d2pZ    = abs(playerZ - enemyZ);  //distance to player

                //CERCAR --- SOLO CALCULAR LOS ENEMIGOS CERCANOS (pero no demasiado cerca)
                //VER EN QUE CUADRANTE ESTA EL ENEMIGO CON RESPECTO AL JUGADOR
                if(d2pX>50 && d2pX<300){
                    if(enemyX<playerX)       m_moreEnemiesX--; //IZQ
                    else                     m_moreEnemiesX++; //DER
                }
                if(d2pZ>50 && d2pZ<300){
                    if(enemyZ<playerZ)       m_moreEnemiesZ++; //DOWN
                    else                     m_moreEnemiesZ--; //UP
                }
            }

        }
    }
}

void Scene::Update()
{
    if(mainPlayer->getHealth()<=0){
        Game::getInstance()->ChangeState(GSDead::getInstance());
    }

    updateEnemies();  // Devuelve los parametros para la camara inteligente m_moreEnemiesX , m_moreEnemiesZ
    GEInstance->updateCamera(mainPlayer->getPosition(), m_moreEnemiesX, m_moreEnemiesZ);

    mainPlayer->update(); //Posición actualizada de Irrlicht Player

    // Actualizamos los playermates
    int num = NetInstance->getNumPlayerMates();
    for(int i=0; i<num; i++)
    {
        PlayerMate* p = NetInstance->getPlayerMate(i);
        p->update();
    }

    updateProjectiles();
    updateProjectilesGrenade();
    updateConsumables(mainPlayer);
    m_triggerSystem.Update();
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
void Scene::updateProjectilesGrenade()
{
    unsigned int i=0;
    while(i<m_projectilesGrenades.size())
    {
        m_projectilesGrenades[i]->update();
        if (m_projectilesGrenades[i]->getExploded())
        {
            // Borramos granada
            delete m_projectilesGrenades[i];
            m_projectilesGrenades.erase(m_projectilesGrenades.begin()+i);
            i--;
        }
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
void Scene::deleteProjectileGrenade(unsigned int i)
{
    if (i<m_projectilesGrenades.size())
    {
        delete m_projectilesGrenades[i];
        m_projectilesGrenades.erase(m_projectilesGrenades.begin()+i);
    }
}

////////////
void Scene::createProjectile(dwe::vec3f origin, float angle, std::string weapon)
{
    m_projectiles.push_back(GEInstance->createProjectile(origin, angle, weapon));
}

////////////
void Scene::createProjectileGrenade(dwe::vec3f origin, float angle)
{
    m_projectilesGrenades.push_back(GEInstance->createProjectileGrenade(origin, angle));
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

////////////////////////////

//CREATE CONSUMABLES
void Scene::createSpeedBoost(float px, float py, float pz)          { m_consumables.push_back(GEInstance->createSpeedBoost(px, py, pz));    }
void Scene::createMedkit(float px, float py, float pz)              { m_consumables.push_back(GEInstance->createMedkit(px, py, pz));        }
void Scene::createCShotgun(float px, float py, float pz)            { m_consumables.push_back(GEInstance->createCShotgun(px, py, pz));      }
void Scene::createCRifle(float px, float py, float pz)              { m_consumables.push_back(GEInstance->createCRifle(px, py, pz));        }
void Scene::createAmmoGun(float px, float py, float pz)             { m_consumables.push_back(GEInstance->createAmmoGun(px, py, pz));       }
void Scene::createMagnetKey(int id, float px, float py, float pz)   { m_consumables.push_back(GEInstance->createMagnetKey(id, px, py, pz)); }
