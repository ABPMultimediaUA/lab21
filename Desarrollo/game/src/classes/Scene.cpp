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

///////////////////////////////
Scene* Scene::Instance()
{
  static Scene instance;

  return &instance;
}

Scene::Scene() : navGraph(false)
{
    cout<<"IN Scene constructor"<<endl;
    //ctor
}
///////////////////////////////
void Scene::Init()
{
    timeLastProjectil       = 0;
    m_timeLastEnemyActive   = 0;
    m_timeEnemyActive       = 5.0;  // En segundos
    m_posMother             = dwe::vec3f(0,62.0,-1617.0);


    /**********************************/
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
    /**********************************/
    // Llaves
    //llave=GEInstance->createMagnetKey(0, 50, 0, 350);
    //llaveCogida=false;

    /******************Waypoints*******************/

    NavGraphNode node0(0, dwe::vec2f(-200, 200));
    /*NavGraphNode node1(1, dwe::vec2f(-200, 100));
    NavGraphNode node2(2, dwe::vec2f(-100, 100));
    NavGraphNode node3(3, dwe::vec2f(-100, 200));

    NavGraphNode node4(4, dwe::vec2f(-150, 150));

    NavGraphNode node5(5, dwe::vec2f(-175, 0));
    NavGraphNode node6(6, dwe::vec2f(-125, 0));

    NavGraphNode node7(7, dwe::vec2f(-150, 50));*/

    navGraph.addNode(node0);
    /*navGraph.addNode(node1);
    navGraph.addNode(node2);
    navGraph.addNode(node3);
    navGraph.addNode(node4);
    navGraph.addNode(node5);
    navGraph.addNode(node6);
    navGraph.addNode(node7);

    NavGraphEdge edge01(0, 1, 100);
    NavGraphEdge edge03(0, 3, 100);
    NavGraphEdge edge04(0, 4, 70.710678);

    NavGraphEdge edge12(1, 2, 100);
    NavGraphEdge edge14(1, 4, 70.710678);
    NavGraphEdge edge15(1, 5, 103.07764);

    NavGraphEdge edge23(2, 3, 100);
    NavGraphEdge edge24(2, 4, 70.710678);
    NavGraphEdge edge26(2, 6, 103.07764);

    NavGraphEdge edge34(3, 4, 70.710678);

    NavGraphEdge edge75(7, 5, 55.901699);
    NavGraphEdge edge76(7, 6, 55.901699);


    navGraph.addEdge(edge01);
    navGraph.addEdge(edge03);
    navGraph.addEdge(edge04);
    navGraph.addEdge(edge12);
    navGraph.addEdge(edge14);
    navGraph.addEdge(edge15);
    navGraph.addEdge(edge23);
    navGraph.addEdge(edge24);
    navGraph.addEdge(edge26);
    navGraph.addEdge(edge34);
    navGraph.addEdge(edge75);
    navGraph.addEdge(edge76);*/

    /*Shotgun* node = createShotgun(-100,10,100);
    node = createShotgun(-100,10,200);*/
    Shotgun* node = createShotgun(-200,10,200);
    /*node = createShotgun(-200,10,100);
    node = createShotgun(-150,10,150);
    node = createShotgun(-175,10,0);
    node = createShotgun(-125,10,0);
    node = createShotgun(-150,10,50);*/


    // MEDKITS
    //createMedkit(-300, 10, 200);

    // SPEEDBOOST
    createSpeedBoost(-300, 10, 200);

    // LLAVES
    createMagnetKey(0, 105, 0, 1345);
    createMagnetKey(1, 785, 0, 1045);
    createMagnetKey(2, 2255, 0, 505);

    // LLAVES
    createMagnetKey(0, 105, 0, 1345);
    createMagnetKey(1, 785, 0, 1045);
    createMagnetKey(2, 2255, 0, 505);

    // GUN - SHOTGUN - RIFLE
    gun = createGun(0,0,0); // Creo el arma inicial del player
    shotgun = createShotgun(-100,10,-210);
    rifle = createRifle(-100,10,-200);

    // Creación de jugador
    mainPlayer = GEInstance->createMainPlayer(gun);
    //TODO he puesto posicion para pruebas mainPlayer->setPosition(dwe::vec3f(-1205-((NetInstance->getParticipantOrder()-1)*30),24,1150));
                mainPlayer->setPosition(dwe::vec3f(140-((NetInstance->getParticipantOrder()-1)*30),24,80));
    World->setMainPlayer(mainPlayer);


    createEnemies();

    GEInstance->createCamera();
}

void Scene::createEnemies()
{
    m_numEnemies = m_numActiveEnemies = 11;
    m_enemies = new TEnemy[m_numEnemies];
    m_enemies[ 0].enemy = GEInstance->createEnemyHumanoid(-200,24,200);
    m_enemies[ 1].enemy = GEInstance->createEnemyDog(530,24,390);
    m_enemies[ 2].enemy = GEInstance->createEnemyBat(475,24,90);
    m_enemies[ 3].enemy = GEInstance->createEnemyGuardian(-310,24,100);
    m_enemies[ 4].enemy = GEInstance->createEnemyLegless(-630,24,410);
    m_enemies[ 5].enemy = GEInstance->createEnemyHumanoid(300,24,1150);
    m_enemies[ 6].enemy = GEInstance->createEnemyHumanoid(-300,24,570);
    m_enemies[ 7].enemy = GEInstance->createEnemyHumanoid(1470,24,330);
    m_enemies[ 8].enemy = GEInstance->createEnemyHumanoid(1350,24,180);
    m_enemies[ 9].enemy = GEInstance->createEnemyHumanoid(1860,24,130);
    m_enemies[10].enemy = GEInstance->createEnemyHumanoid(1970,24,230);

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
    //return m_enemies.size();
    return m_numActiveEnemies;
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
                dwe::vec3f pos = m_posMother;
                pos.z += 150;
                m_enemies[i].enemy->setPosition(pos);
                m_enemies[i].enemy->resetHealth();
                m_enemies[i].enemy->setPhysicsActive(true);
                m_enemies[i].active = true;
                m_numActiveEnemies++;
                m_timeLastEnemyActive = World->getTimeElapsed();
                std::cout << "Activado\n";
            }
        }
        else
        {
            //Enemigo activo
            // Borrado de enemigos (desactivacion)
            if (m_enemies[i].enemy->getHealth()<=0)
            {
                m_enemies[i].active = false;
                m_enemies[i].enemy->setPhysicsActive(false);

                // Si estaban todos los enemigos activos, reinicio contador
                if (m_numEnemies == m_numActiveEnemies)
                    m_timeLastEnemyActive = World->getTimeElapsed();

                m_numActiveEnemies--;
                // TODO desactivar nodo
                NetInstance->removeNetEnemy(m_enemies[i].enemy);
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

    mainPlayer->readEvents(); // Read keyboard and mouse inputs for de player


    // comprobamos si dispara
    if (   GEInstance->receiver.isLeftButtonPressed()
        && mainPlayer->shoot(World->getTimeElapsed() - timeLastProjectil) )
    {
        timeLastProjectil = World->getTimeElapsed();
    }


    // comprobamos si dispara granadas
    if(GEInstance->receiver.isKeyDown(KEY_GRENADE) && (World->getTimeElapsed() - timeLastProjectil)> 0.2 ){
        NetInstance->sendBroadcast(ID_PROJECTILEGRENADE_CREATE, mainPlayer->getPosition(), mainPlayer->getRotation().y); // Enviamos mensaje para crear projectilgrenade
        if (mainPlayer->getGrenades() > 0) //
        {
            NetInstance->sendBroadcast(ID_PROJECTILEGRENADE_CREATE, mainPlayer->getPosition(), mainPlayer->getRotation().y); // Enviamos mensaje para crear projectilgrenade

            mainPlayer->throwGrenade();

            timeLastProjectil = World->getTimeElapsed();

            mainPlayer->setGrenades(mainPlayer->getGrenades()-1); //
        }//
    }

    //UPDATE

    mainPlayer->update(shotgun, rifle); //Posición actualizada de Irrlicht Player

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
    updatePlayerWeapons(mainPlayer, mainPlayer->getPlayerWeapons());
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
        if (m_projectilesGrenades[i]->getCollides())
        {
            m_projectilesGrenades[i]->setVelocity(dwe::vec2f(0,0));
        }
        if(m_projectilesGrenades[i]->getVelocity().x==0 && m_projectilesGrenades[i]->getVelocity().y==0){
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
    AEInstance->Play2D("media/DisparoEscopeta.wav");
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

void Scene::updatePlayerWeapons(Player* mainplayer, Firearm** weapons)
{
    //cout << "- "<< mainplayer->getCurrentWeaponType() << ":" << eRifle << endl;
    // TODO dibujar bien y solo la actual
    for (uint8_t i=0; i<3; i++)
        if (weapons[i])
            weapons[i]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    /*if  (mainplayer->getCurrentWeaponType() == eGun){
        weapons[0]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }else if (mainplayer->getCurrentWeaponType() == eShotgun){
        weapons[1]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }else if (mainplayer->getCurrentWeaponType() == eRifle){
        weapons[2]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }*/
}

////////////////////////////

//CREATE CONSUMABLES
void Scene::createSpeedBoost(float px, float py, float pz)          { m_consumables.push_back(GEInstance->createSpeedBoost(px, py, pz));    }
void Scene::createMedkit(float px, float py, float pz)              { m_consumables.push_back(GEInstance->createMedkit(px, py, pz));        }
void Scene::createCShotgun(float px, float py, float pz)            { m_consumables.push_back(GEInstance->createCShotgun(px, py, pz));      }
void Scene::createCRifle(float px, float py, float pz)              { m_consumables.push_back(GEInstance->createCRifle(px, py, pz));        }
void Scene::createAmmoGun(float px, float py, float pz)             { m_consumables.push_back(GEInstance->createAmmoGun(px, py, pz));       }
void Scene::createMagnetKey(int id, float px, float py, float pz)   { m_consumables.push_back(GEInstance->createMagnetKey(id, px, py, pz)); }

//CREATE WEAPONS
Gun* Scene::createGun(float px, float py, float pz)         {   return GEInstance->createGun(px, py, pz);   }
Shotgun* Scene::createShotgun(float px, float py, float pz) {   return GEInstance->createShotgun(px, py, pz);      }
Rifle* Scene::createRifle(float px, float py, float pz)     {   return GEInstance->createRifle(px, py, pz);        }

