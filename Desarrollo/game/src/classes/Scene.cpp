#include "Scene.h"
#include "WorldInstance.h"
#include "Projectile.h"
#include "SpeedBoost.h"
#include "Medkit.h"
#include "Consumable.h"
#include "AmmoGun.h"
#include "CShotgun.h"
#include "CRifle.h"
#include "Game.h"
#include "GSDead.h"
#include "NavGraphNode.h"
#include "NavGraphEdge.h"

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
            if (GEInstance->receiver.isKeyDown(KEY_RETURN))
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
    NavGraphNode node1(1, dwe::vec2f(-200, 100));
    NavGraphNode node2(2, dwe::vec2f(-100, 100));
    NavGraphNode node3(3, dwe::vec2f(-100, 200));

    NavGraphNode node4(4, dwe::vec2f(-150, 150));

    NavGraphNode node5(5, dwe::vec2f(-175, 0));
    NavGraphNode node6(6, dwe::vec2f(-125, 0));

    NavGraphNode node7(7, dwe::vec2f(-150, 50));

    navGraph.addNode(node0);
    navGraph.addNode(node1);
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
    navGraph.addEdge(edge76);

    Shotgun* node = createShotgun(-100,10,100);
    node = createShotgun(-100,10,200);
    node = createShotgun(-200,10,200);
    node = createShotgun(-200,10,100);
    node = createShotgun(-150,10,150);
    node = createShotgun(-175,10,0);
    node = createShotgun(-125,10,0);
    node = createShotgun(-150,10,50);


    // MEDKITS
    createMedkit(-300, 10, 200);

    // GUN - SHOTGUN - RIFLE
    gun = createGun(0,0,0); // Creo el arma inicial del player
    shotgun = createShotgun(-100,10,-210);
    rifle = createRifle(-100,10,-200);

    // Creación de jugador
    mainPlayer = GEInstance->createMainPlayer(gun);
    mainPlayer->setPosition(dwe::vec3f(140-((NetInstance->getParticipantOrder()-1)*30),24,80));
    World->setMainPlayer(mainPlayer);
    cout << "Barra de vida: " << mainPlayer->getHealth() << endl;

    ////////////////////////////////
    //         Enemigos           //
    ////////////////////////////////
    enemyHumanoid = GEInstance->createEnemyHumanoid();
    enemyHumanoid->setPosition(dwe::vec3f(-200,24,200));
    m_enemies.push_back(enemyHumanoid);

    /*for(int i=0; i<4; i++){
        enemyHumanoid = GEInstance->createEnemyHumanoid();
        enemyHumanoid->setPosition(dwe::vec3f(500+(i*10),24,250+(i*80) ));
        m_enemies.push_back(enemyHumanoid);
    }

    for(int i=0; i<4; i++){
        enemyHumanoid = GEInstance->createEnemyHumanoid();
        enemyHumanoid->setPosition(dwe::vec3f(-300+(i*10),24,400+(i*80) ));
        m_enemies.push_back(enemyHumanoid);
    }*/
    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////

    // Creación de enemigo Dog
    enemyDog = GEInstance->createEnemyDog();
    enemyDog->setPosition(dwe::vec3f(100,24,80));

    //Joint try
    joint_try = GEInstance->createNode("media/the101010box");   //ESTAS SON LAS BUENAS
    joint_try->setPosition(dwe::vec3f(0,10,-120));
    bjoint = new EntityPhysics();
    bjoint->createJointBody(dwe::vec3f(0,10,-120)); // createJointBody(dwe::vec3f(0,10,120));

    GEInstance->createCamera();

    //rmm Cheat: la primera vez que creo el projectile va muy lento, no se pq
    createProjectile(dwe::vec3f(1.0, 1.0, 1.0), 0.5, "gunBullet");
    deleteProjectile(0);
    timeLastProjectil = 0;
}

///////////////////////////////
void Scene::Destroy(){
    //delete llave;
    //delete enemyDog;
    delete mainPlayer; mainPlayer=0;
    delete gun;
    delete shotgun;
    delete rifle;
    while(m_enemies.size()>0){
        enemyHumanoid=(Humanoid*)m_enemies.back();
        m_enemies.pop_back();
        NetInstance->removeNetEnemy(enemyHumanoid);
        delete enemyHumanoid;
    }

    while(m_projectiles.size()>0){
        m_projectiles.pop_back();
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

void Scene::Update()
{
    if(mainPlayer->getHealth()<=0){
        Game::getInstance()->ChangeState(GSDead::getInstance());
    }
    for(size_t i=0; i<m_enemies.size(); i++){ //recorre
            Enemy* enemy=m_enemies.at(i);
            if(enemy && enemy->getHealth()<=0){
                m_enemies.erase(m_enemies.begin()+i);

                NetInstance->removeNetEnemy(enemy);
                delete enemy;
                enemy=0;
                enemyHumanoid = 0;
            }
    }


    //////////////////////////////////////////
    //         CAMARA INTELIGENTE           //
    //////////////////////////////////////////
    //PARA CAMARA INTELIGENTE --- La idea es contar cuántos enemigos tenemos a cada extremo y acercar la cámara según el extremo que más haya.
    moreEnemiesX = 0;
    moreEnemiesZ = 0;
    //int dist2player = 0;
    for(size_t e=0; e<m_enemies.size(); e++){
        if(m_enemies[e]){
            int playerX = mainPlayer->getPosition().x;      int playerZ = mainPlayer->getPosition().z;
            int enemyX  = m_enemies[e]->getPosition().x;    int enemyZ  = m_enemies[e]->getPosition().z;
            int d2pX    = abs(playerX - enemyX);            int d2pZ    = abs(playerZ - enemyZ);  //distance 2 player

            //CERCAR --- SOLO CALCULAR LOS ENEMIGOS CERCANOS (pero no demasiado cerca)
            //VER EN QUE CUADRANTE ESTA EL ENEMIGO CON RESPECTO AL JUGADOR
            if(d2pX>50 && d2pX<300){
                if(enemyX<playerX)       moreEnemiesX--; //IZQ
                else                     moreEnemiesX++; //DER
            }
            if(d2pZ>50 && d2pZ<300){
                if(enemyZ<playerZ)       moreEnemiesZ++; //DOWN
                else                     moreEnemiesZ--; //UP
            }
        }
    }
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    GEInstance->updateCamera(mainPlayer->getPosition(), moreEnemiesX, moreEnemiesZ);
    mainPlayer->readEvents(); // Read keyboard and mouse inputs for de player

    for(size_t e=0; e<m_enemies.size(); e++) //recorre
        if(m_enemies[e])
            m_enemies[e]->update();

    // comprobamos si dispara
    if((World->getTimeElapsed() - timeLastProjectil)> 200 && GEInstance->receiver.isLeftButtonPressed()){
        if (mainPlayer->getAmmo(0) > 0) //
        {
            mainPlayer->shoot();

            timeLastProjectil = World->getTimeElapsed();

            mainPlayer->setAmmo(0, mainPlayer->getAmmo(0)-1); //
        }//
    }

    //UPDATE

    mainPlayer->update(shotgun, rifle); //Posición actualizada de Irrlicht Player
    updateProjectiles();
    updateConsumables(mainPlayer);
    updatePlayerWeapons(mainPlayer, mainPlayer->getPlayerWeapons());

    //update box of box2d
    joint_try->setPosition(dwe::vec3f(bjoint->getPosEntity().x,bjoint->getPosEntity().y,bjoint->getPosEntity().z));

    /*
    // Coger la llave
    if(!llaveCogida)
    {
        NO SE DEBE USAR INTERSECTS RMM if(mainPlayer->getNode()->intersects(llave->getNode()->getNode()))
        {
            llaveCogida=true;
            mainPlayer->setMKeys(llave->getId());
            delete llave;
            llave = 0;
        }
    }
    */
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
            cout<<"colision"<<endl;
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
void Scene::createProjectile(dwe::vec3f origin, float angle, std::string weapon)
{
    m_projectiles.push_back(GEInstance->createProjectile(origin, angle, weapon));
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
    if  (mainplayer->getCurrentWeaponType() == eGun){
        weapons[0]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }else if (mainplayer->getCurrentWeaponType() == eShotgun){
        weapons[1]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }else if (mainplayer->getCurrentWeaponType() == eRifle){
        weapons[2]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }
}

////////////////////////////

//CREATE CONSUMABLES
void Scene::createSpeedBoost(float px, float py, float pz)  { m_consumables.push_back(GEInstance->createSpeedBoost(px, py, pz));    }
void Scene::createMedkit(float px, float py, float pz)      { m_consumables.push_back(GEInstance->createMedkit(px, py, pz));        }
void Scene::createCShotgun(float px, float py, float pz)    { m_consumables.push_back(GEInstance->createCShotgun(px, py, pz));      }
void Scene::createCRifle(float px, float py, float pz)      { m_consumables.push_back(GEInstance->createCRifle(px, py, pz));        }
void Scene::createAmmoGun(float px, float py, float pz)     { m_consumables.push_back(GEInstance->createAmmoGun(px, py, pz));       }

//CREATE WEAPONS
Gun* Scene::createGun(float px, float py, float pz)         {   return GEInstance->createGun(px, py, pz);   }
Shotgun* Scene::createShotgun(float px, float py, float pz) {   return GEInstance->createShotgun(px, py, pz);      }
Rifle* Scene::createRifle(float px, float py, float pz)     {   return GEInstance->createRifle(px, py, pz);        }

