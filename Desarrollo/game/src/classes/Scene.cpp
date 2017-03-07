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

Scene* Scene::Instance()
{
  static Scene instance;

  return &instance;
}

Scene::Scene()
{
    cout<<"IN Scene constructor"<<endl;
    //ctor
}

void Scene::Init()
{
    /**********************************/
    if (NetInstance->isMultiplayer())
    {
        if (NetInstance->isServer())
            GEInstance->addMessageLine(L"Pulsa intro cuando esten todos los jugadores");
        else
            GEInstance->addMessageLine(L"Esperando a que el servidor de la partida inicie el juego");
        // En startGame solo se inicia si es el servidor
        while (!NetInstance->getGameStarted() && GEInstance->isRunning())
        {
            GEInstance->draw();
            NetInstance->update();
            if (GEInstance->receiver.isKeyDown(KEY_RETURN))
                NetInstance->startGame();
        }
    }
    GEInstance->addMessageLine(L"Partida iniciada");
    /**********************************/
    // Llaves
    //llave=GEInstance->createMagnetKey(0, 50, 0, 350);
    //llaveCogida=false;

    // GUN - SHOTGUN - RIFLE
    gun = createGun(0,0,0); // Creo el arma inicial del player
    shotgun = createShotgun(-100,10,210);
    rifle = createRifle(-100,10,200);

    // Creación de jugador
    mainPlayer = GEInstance->createMainPlayer(gun);
    mainPlayer->setPosition(dwe::vec3f(140-((NetInstance->getParticipantOrder()-1)*30),24,-80));
    mainPlayer->setHealth(10);
    World->setMainPlayer(mainPlayer);
    cout << "Barra de vida: " << mainPlayer->getHealth() << endl;

    ////////////////////////////////
    //         Enemigos           //
    ////////////////////////////////
    for(int i=0; i<4; i++){
        enemyHumanoid = GEInstance->createEnemyHumanoid();
        enemyHumanoid->setPosition(dwe::vec3f(500+(i*10),24,-250+(i*80) ));
        //enemyHumanoid->setRotation(dwe::vec3f(0, 90.f, 0));
        m_enemies.push_back(enemyHumanoid);
    }

    for(int i=0; i<4; i++){
        enemyHumanoid = GEInstance->createEnemyHumanoid();
        enemyHumanoid->setPosition(dwe::vec3f(-300+(i*10),24,-400+(i*80) ));
        //enemyHumanoid->setRotation(dwe::vec3f(0, 90.f, 0));
        m_enemies.push_back(enemyHumanoid);
    }
    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////

    // Creación de enemigo Dog
    //enemyDog = GEInstance->createEnemyDog();
    //enemyDog->setPosition(dwe::vec3f(-50,-170,100));

    //Joint try
    joint_try = GEInstance->createNode("media/the101010box");   //ESTAS SON LAS BUENAS
    joint_try->setPosition(dwe::vec3f(0,10,120));
    bjoint = new EntityPhysics();
    bjoint->createJointBody(dwe::vec3f(0,10,120)); // createJointBody(dwe::vec3f(0,10,120));

    //CAMERA (nodo padre, posición, directión)
    camera1 = GEInstance->getSMGR()->addCameraSceneNode(0,  vector3df(0,0,0), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
    GEInstance->getSMGR()->setActiveCamera(camera1); //Activar cámara

    //rmm Cheat: la primera vez que creo el projectile va muy lento, no se pq
    createProjectile(dwe::vec3f(1.0, 1.0, 1.0), 0.5);
    deleteProjectile(0);
    timeLastProjectil = 0;
}

void Scene::Destroy(){
    //delete llave;
    //delete enemyDog;
    delete mainPlayer; mainPlayer=0;
    delete gun;
    delete shotgun;
    delete rifle;
    for(int i=0; i<m_enemies.size(); i++){
        enemyHumanoid=(Humanoid*)m_enemies[i];
        m_enemies.erase(m_enemies.begin()+i);
        NetInstance->removeNetEnemy(enemyHumanoid);
        delete enemyHumanoid;
    }
    for(int i=0; i<m_projectiles.size(); i++){
        m_projectiles.erase(m_projectiles.begin()+i);
    }
    for(int i=0; i<m_consumables.size(); i++){
        m_consumables.erase(m_consumables.begin()+i);
    }
    delete joint_try;
    delete bjoint;
    //delete camera1;
    cout<<"DELETE ALL"<<endl;
}

Scene::~Scene()
{

if(mainPlayer)
    Destroy();

}

void Scene::Update()
{

    if(mainPlayer->getHealth()<=0){
        Game::getInstance()->ChangeState(GSDead::getInstance());
    }
    for(int i=0; i<m_enemies.size(); i++){ //recorre
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
    int dist2player = 0;
    for(int e=0; e<m_enemies.size(); e++){
        if(m_enemies[e]){
            int playerX = mainPlayer->getPosition().x;      int playerZ = mainPlayer->getPosition().z;
            int enemyX  = m_enemies[e]->getPosition().x;    int enemyZ  = m_enemies[e]->getPosition().z;
            int d2pX    = abs(playerX - enemyX);            int d2pZ    = abs(playerZ - enemyZ);

            //CERCAR --- SOLO CALCULAR LOS ENEMIGOS CERCANOS (pero no demasiado cerca)
            //VER EN QUE CUADRANTE ESTA EL ENEMIGO CON RESPECTO AL JUGADOR
            if(d2pX>50 && d2pX<300){
                if(enemyX<playerX)       moreEnemiesX--; //IZQ
                else                     moreEnemiesX++; //DER
            }
            if(d2pZ>50 && d2pZ<300){
                if(enemyZ<playerZ)       moreEnemiesZ--; //DOWN
                else                     moreEnemiesZ++; //UP
            }

            //ENEMIGO MAS ALEJADO DEL GRUPO MAS GRANDE

        }
    }

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////


    GEInstance->updateCamera(mainPlayer->getPosition(), moreEnemiesX, moreEnemiesZ);
    mainPlayer->readEvents(); // Read keyboard and mouse inputs for de player

    for(int e=0; e<m_enemies.size(); e++) //recorre
<<<<<<< HEAD
           // m_enemies[e]->update();
=======
        if(m_enemies[e])
            m_enemies[e]->update();
>>>>>>> master

    // comprobamos si dispara

    if((World->getTimeElapsed() - timeLastProjectil)> 200 && GEInstance->receiver.isLeftButtonPressed()){
        NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, mainPlayer->getPosition(), mainPlayer->getRotation().y); // Enviamos mensaje para crear projectil
        if (mainPlayer->getCurrentWeaponType() == eGun && mainPlayer->getAmmo(0) > 0) //
        {
            NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, mainPlayer->getPosition(), mainPlayer->getRotation().y); // Enviamos mensaje para crear projectil

            createProjectile(mainPlayer->getPosition(), mainPlayer->getRotation().y);
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
        if(mainPlayer->getNode()->intersects(llave->getNode()->getNode()))
        {
            llaveCogida=true;
            mainPlayer->setMKeys(llave->getId());
            delete llave;
            llave = 0;
        }
    }
    */
    /*
    //rmm:cheat, cojo todo
    if (GEInstance->receiver.isKeyDown(KEY_KEY_C))
    {
        // Cojo llave
        if(llave!=0)
        {
            llaveCogida=true;
            mainPlayer->setMKeys(llave->getId());
        }

        //Activo todo
        for(int i=0; i<3; i++)
        {
            if(i==2)
            {
                if(mainPlayer->getMKey(((Generator*)entities[i])->getNum()))
                    triggers[i]->triggered(entities[i]);
            }
            else if(i==0 || i==1)
                triggers[i]->triggered(entities[i]);
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
    //cout << "- "<< mainplayer->getCurrentWeaponType() << ":" << eRifle << endl;
    if  (mainplayer->getCurrentWeaponType() == eGun){
        weapons[0]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }else if (mainplayer->getCurrentWeaponType() == eShotgun){
        weapons[1]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }else if (mainplayer->getCurrentWeaponType() == eRifle){
        weapons[2]->setPosition(dwe::vec3f(mainplayer->getPosition().x , 20 , mainplayer->getPosition().z + 10));
    }
}

////////////
void Scene::createEnemyHumanoid(dwe::vec3f origin, float angle){
   // m_enemies.push_back(GEInstance->createEnemyHumanoid(origin, angle));
}


//CREATE CONSUMABLES
void Scene::createSpeedBoost(float px, float py, float pz)  { m_consumables.push_back(GEInstance->createSpeedBoost(px, py, pz));    }
void Scene::createMedkit(float px, float py, float pz)      { m_consumables.push_back(GEInstance->createMedkit(px, py, pz));        }
void Scene::createCShotgun(float px, float py, float pz)    { m_consumables.push_back(GEInstance->createCShotgun(px, py, pz));      }
void Scene::createCRifle(float px, float py, float pz)      { m_consumables.push_back(GEInstance->createCRifle(px, py, pz));        }
void Scene::createAmmoGun(float px, float py, float pz)     { m_consumables.push_back(GEInstance->createAmmoGun(px, py, pz));       }

//CREATE WEAPONS
Gun* Scene::createGun(float px, float py, float pz)         {   return GEInstance->createGun(px, py, pz);   }
Shotgun* Scene::createShotgun(float px, float py, float pz) {   GEInstance->createShotgun(px, py, pz);      }
Rifle* Scene::createRifle(float px, float py, float pz)     {   GEInstance->createRifle(px, py, pz);        }

