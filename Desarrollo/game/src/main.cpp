#include <iostream>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GraphicsEngine.h>
#include <time.h>

#include "WorldInstance.h"

#include "NetGame.h"
#include "Player.h"
#include "Bat.h"
#include "Mother.h"
#include "Guardian.h"
#include "Legless.h"
#include "Dog.h"
#include "Humanoid.h"

#include "Door.h"
#include "Projectile.h"
#include "Generator.h"
#include "MagnetKey.h"
#include "SpeedBoost.h"

#include "TriggerDoor.h"
#include "TriggerGenerator.h"

#include "Selector.h"
#include "Sequence.h"

#include "Pathplanning.h"
#include "Perception.h"

#include "CheckIfDoorIsOpenTask.h"
#include "ApproachDoorTask.h"
#include "OpenDoorTask.h"
#include "WalkThroughDoorTask.h"
#include "CloseDoorTask.h"
#include "PathplanningTask.h"
#include "PerceptionTask.h"
#include "PatrolTask.h"

#include "EntityPhysics.h"
#include "ScenaryElement.h"

#define NUM_ENTITIES 3


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    NetInstance->open();  // Inicializar motor de red

	GEInstance->init();  // Inicializar motor gráfico

    clock_t t1;          // Creo reloj
    clock_t t2;
    clock_t  t;

    // Creación de jugador
	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->setPosition(dwe::vec3f(140-((NetInstance->getParticipantOrder()-1)*30),24,-80));
	mainPlayer->setLife(100);
	cout << "Barra de vida: " << mainPlayer->getLife() << endl;

    //para la camara, movimiento de descentrar
    float tarLR = 0;
    float tarUD = 0;


    // Creación de escenario
	dwe::Node* suelo = GEInstance->createNode("media/suelo");
	suelo->setPosition(dwe::vec3f(0,0,0));

    ScenaryElement* wall01 = GEInstance->createWall("media/pared01");wall01->setPosition(dwe::vec3f(-35,   36.3, 135.9));
    ScenaryElement* wall02 = GEInstance->createWall("media/pared02");wall02->setPosition(dwe::vec3f(120.4, 36.3, 135.9));
    ScenaryElement* wall03 = GEInstance->createWall("media/pared03");wall03->setPosition(dwe::vec3f(42.7,  36.3, -132.2));
    ScenaryElement* wall04 = GEInstance->createWall("media/pared04");wall04->setPosition(dwe::vec3f(-84.9, 36.3, 2.2));
    ScenaryElement* wall05 = GEInstance->createWall("media/pared05");wall05->setPosition(dwe::vec3f(170.5, 36.3, 82.6));
    ScenaryElement* wall06 = GEInstance->createWall("media/pared06");wall06->setPosition(dwe::vec3f(170.5, 36.3, -76.7));
    ScenaryElement* wall07 = GEInstance->createWall("media/pared07");wall07->setPosition(dwe::vec3f(304.8, 36.3, -132.2));
    ScenaryElement* wall08 = GEInstance->createWall("media/pared08");wall08->setPosition(dwe::vec3f(304.8, 36.3, 133.8));
    ScenaryElement* wall09 = GEInstance->createWall("media/pared09");wall09->setPosition(dwe::vec3f(432.7, 36.3, 2.2));
    ScenaryElement* wall10 = GEInstance->createWall("media/pared10");wall10->setPosition(dwe::vec3f(-84.4, 36.3, 269.9));
    ScenaryElement* wall11 = GEInstance->createWall("media/pared11");wall11->setPosition(dwe::vec3f(170.8, 36.3, 269.6));
    ScenaryElement* wall12 = GEInstance->createWall("media/pared12");wall12->setPosition(dwe::vec3f(43.1,  36.3, 399.8));

    Entity **entities; // Array de entidades
    Entity **sector; // Sector no funcional que se le asigna a un generador
    Trigger **triggers; // Triggers
    entities=new Entity*[NUM_ENTITIES];
    sector=new Entity*[1];
    triggers=new Trigger*[3];

    // Puertas
    entities[0]=GEInstance->createDoor(0, true, 43.5, 0, 135.9);
    entities[1]=GEInstance->createDoor(3, false, 0, 0, 0); // false //170,0,0
    sector[0]=entities[1];


    // Generadores
    entities[2]=GEInstance->createGenerator(0, false, -50, 0, -50); // false
    ((Generator*)entities[2])->setSector(sector, 1);

    // Llaves
    MagnetKey *llave=GEInstance->createMagnetKey(0, 50, 0, 350);
    bool llaveCogida=false;

    // SpeedBoost
    SpeedBoost *speedboost = GEInstance->createSpeedBoost(0, 210, 10, 10);
    bool hasSpeedBoost = false;
    int t_speed = 0;

    // Triggers -> 0 Door, 1 Generator
    triggers[0]=GEInstance->createTrigger(0, 43.5, 0, 135.9);
    triggers[1]=GEInstance->createTrigger(0, 170, 0, 0);
    triggers[2]=GEInstance->createTrigger(1, -50, 0, -50);


    ////////////////////////////////
    // Enemigos
    ////////////////////////////////

    // Creación de enemigo Humanoide
	Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
	//enemyHumanoid->setPosition(dwe::vec3f(43.5,24,-100));
	enemyHumanoid->setPosition(dwe::vec3f(400,24,100));
	enemyHumanoid->setRotation(dwe::vec3f(0, 90.f, 0));

	// Creación de enemigo Dog
	Dog* enemyDog = GEInstance->createEnemyDog();
	enemyDog->setPosition(dwe::vec3f(-50,-170,100)); // No está centrado :(



    //Creación fov
    dwe::Node* fovnode = GEInstance->createNode("media/fov");
    //fovnode->setMaterialFlag(EMF_WIREFRAME, true);
    fovnode->setPosition(enemyHumanoid->getPosition());
    fovnode->setRotation(enemyHumanoid->getRotation());


	// Creacion objeto Proyectil
	Projectile *projectile = 0;

    //Salud
	dwe::Node* first_aid = GEInstance->createNode("media/First_Aid_Med_Kit/FirstAidMedKit");
	first_aid->setPosition(dwe::vec3f(400,0,0));

	 //Pistola 1
	dwe::Node* gun_1 = GEInstance->createNode("media/Gun/Gun"); //ESTAS SON LAS BUENAS
	gun_1->setPosition(dwe::vec3f(400,10,100));
	bool haveGun1 = false;

    //Pistola 2
	dwe::Node* gun_2 = GEInstance->createNode("media/Gun/Gun");   //ESTAS SON LAS BUENAS
	gun_2->setPosition(dwe::vec3f(220,10,100));
	bool haveGun2 = false;


    //Joint try
	dwe::Node* joint_try = GEInstance->createNode("media/the101010box");   //ESTAS SON LAS BUENAS
	joint_try->setPosition(dwe::vec3f(0,10,120));
    EntityPhysics* bjoint = new EntityPhysics();
    bjoint->createJointBody(dwe::vec3f(0,10,120)); // createJointBody(dwe::vec3f(0,10,120));


	//////////////////////////////////////////
    //CAMERA (nodo padre, posición, directión)
	ICameraSceneNode* camera1 = GEInstance->getSMGR()->addCameraSceneNode(0,  vector3df(0,0,0), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	GEInstance->getSMGR()->setActiveCamera(camera1); //Activar cámara


    //Creación de objeto perception
    Perception* percep = new Perception();
    Pathplanning* pathp = new Pathplanning();
    float num;//para cambiar de sigilo a rapido


    /*************************** BEHAVIOR TREE **********************************/


    /**** Special nodes ****/

	Selector* selector1 = new Selector;

	Sequence *sequence1 = new Sequence;
    //Sequence *sequence2 = new Sequence;

    /**** Tasks ****/

    /*CheckIfDoorIsOpenTask* checkOpen = new CheckIfDoorIsOpenTask ((Door*)entities[0]);
    ApproachDoorTask* approach = new ApproachDoorTask (enemyHumanoid, (Door*)entities[0]);
	OpenDoorTask* open = new OpenDoorTask ((Door*)entities[0]);
	WalkThroughDoorTask* through = new WalkThroughDoorTask (enemyHumanoid, (Door*)entities[0]);
	CloseDoorTask* close = new CloseDoorTask ((Door*)entities[0]);*/


    PathplanningTask* path = new PathplanningTask(pathp, mainPlayer, enemyHumanoid, fovnode);
    PerceptionTask* perc = new PerceptionTask(percep, mainPlayer, enemyHumanoid, fovnode, path);
	PatrolTask* patrol = new PatrolTask(enemyHumanoid, fovnode);


    /**** Creating the tree ****/

    selector1->addChild(sequence1);
    selector1->addChild(patrol);

    sequence1->addChild(perc);
    sequence1->addChild(path);

    /*sequence1->addChild(checkOpen);
    sequence1->addChild(approach);
    sequence1->addChild(through);
    sequence1->addChild(close);

    sequence2->addChild(approach);
    sequence2->addChild(open);
    sequence2->addChild(through);
    sequence2->addChild(close);*/




    //////////////////////////////////////////////////////////////////

    //rmm Cheat: la primera vez que creo el projectile va muy lento, no se pq
    projectile=GEInstance->createProjectile(mainPlayer->getPosition(), mainPlayer->getRotation().x);
    delete projectile;
    projectile = 0;
    //rmmEnd



    // Esperamos conexion de los demas jugadores
    if (NetInstance->isMultiplayer())
    {
        GEInstance->getSMGR()->getActiveCamera()->setTarget(vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
        GEInstance->getSMGR()->getActiveCamera()->setPosition(vector3df(mainPlayer->getPosition().x,250,mainPlayer->getPosition().z-100));

        while (!NetInstance->getGameStarted() && GEInstance->isRunning())
        {
            GEInstance->draw();
            NetInstance->update();
            if (GEInstance->receiver.isKeyDown(KEY_RETURN))
                NetInstance->startGame();
        }
    }



    ITimer* timer = GEInstance->getDevice()->getTimer();
    float timeStamp = timer->getTime();
    float deltaTime = timer->getTime() - timeStamp;



    /*********************************************************************/
    /**                                                                 **/
    /**                           GAME RUNNING                          **/
    /**                                                                 **/
    /*********************************************************************/
	while(GEInstance->isRunning())
	{
        if(GEInstance->receiver.isKeyDown(KEY_ESCAPE))
        {
            GEInstance->close();
            return 0;
        }

        deltaTime = timer->getTime()-timeStamp; timeStamp=timer->getTime();

        selector1->run();  // Run Behavior Tree

        mainPlayer->readEvents();  // Read keyboard and mouse inputs for de player

        //GET GUN 1
        if(!haveGun1){
            if(mainPlayer->getPosition().x > 390 && mainPlayer->getPosition().x < 410){
                if(mainPlayer->getPosition().z > 90 && mainPlayer->getPosition().z < 110){
                    cout << "Pistola 1 cogida" << endl;
                    haveGun1 = true;
                }
            }
        }

         //GET GUN 2
        if(!haveGun2){
            if(mainPlayer->getPosition().x > 210 && mainPlayer->getPosition().x < 230){
                if(mainPlayer->getPosition().z > 90 && mainPlayer->getPosition().z < 110){
                    cout << "Pistola 2 cogida" << endl;
                    haveGun2 = true;
                }
            }
        }


        // Actualizamos físicas box2d
        World->step(deltaTime);
        World->clearForces();


        // comprobamos si dispara
        if(projectile==0 && GEInstance->receiver.isLeftButtonPressed()){
            projectile=GEInstance->createProjectile(mainPlayer->getPosition(), mainPlayer->getRotation().y);

            //para probar --- cuando disparo pierdo vida
            mainPlayer->setLife(mainPlayer->getLife()-10);
            cout << "CUIDADO!! si disparo pierdo vida. \n Vida actual: " << mainPlayer->getLife() << endl;
        }


        mainPlayer->update(); //Posición actualizada de Irrlicht Player


        for(int cont=0; cont<NUM_ENTITIES; cont++)
            entities[cont]->update();


        if(projectile!=0)
        {
            projectile->update();
            if (projectile->getCollides())
            {
                delete projectile;
                projectile = 0;
            }
        }


        GEInstance->updateCamera(mainPlayer->getPosition());


        //update box of box2d
        joint_try->setPosition(dwe::vec3f(bjoint->getPosEntity().x,bjoint->getPosEntity().y,bjoint->getPosEntity().z));

        // update GUNS
        if(haveGun1)
            gun_1->setPosition(dwe::vec3f(mainPlayer->getPosition().x-20,20,mainPlayer->getPosition().z+10));

        if(haveGun2)
            gun_2->setPosition(dwe::vec3f(mainPlayer->getPosition().x-20,20,mainPlayer->getPosition().z-10));


        GEInstance->draw();


        // Coger la llave
        if(!llaveCogida)
        {
            if(mainPlayer->getNode()->intersects(llave->getNode()->getNode()))
            {
                llaveCogida=true;
                mainPlayer->setMKeys(llave->getId());
                delete llave;
            }
        }


        //////

        float timeStamp2 = timer->getTime();
        // Coger el boost de velocidad
        bool speedBoostTaken = false;
        if(!hasSpeedBoost)
        {
            if (speedboost != 0)
            {
                if(mainPlayer->getNode()->intersects(speedboost->getNode()->getNode()))
                {

                    timeStamp2 = timer->getTime();

                    hasSpeedBoost = true;

                    speedBoostTaken = true;

                    mainPlayer->setSpeed(speedBoostTaken, hasSpeedBoost);

                    speedBoostTaken = false;

                    delete speedboost;

                    speedboost = 0;
                }
            }

        }

        mainPlayer->setSpeed(speedBoostTaken, hasSpeedBoost);

        /////

        // TriggerSystem
        for(int i=0; i<3; i++)
            if(mainPlayer->getNode()->intersects(triggers[i]->getNode()->getNode()))
                if(GEInstance->receiver.isKeyDown(KEY_SPACE))
                    if(i==2){
                        if(mainPlayer->getMKey(((Generator*)entities[i])->getNum()))
                            triggers[i]->triggered(entities[i]);
                    }
                    else if(i==0 || i==1)
                        triggers[i]->triggered(entities[i]);

        //percep->senses(mainPlayer,enemyHumanoid,fovnode,num);  //llamamos a percepcion

        NetInstance->update();
	}

	delete bjoint;

	NetInstance->close();

	return 0;
}


