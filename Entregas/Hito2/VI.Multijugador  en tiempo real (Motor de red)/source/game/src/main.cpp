#include <iostream>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GraphicsEngine.h>
#include <irrKlang.h>
#include <vector>
#include <time.h>
#include <typeinfo>
#include <unistd.h>  //para sleep

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
#include "Generator.h"
#include "MagnetKey.h"
#include "SpeedBoost.h"
#include "Medkit.h"

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

#include "CSetupDevice.h" // Menus

#define NUM_ENTITIES 3

gui::IGUIEnvironment* env = NULL;

void populateSetupWindow(CSetupDevice* setupDevice) {

	if (!setupDevice) return;

	gui::IGUIEnvironment* setupGUI = setupDevice->getGUIEnvironment();
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    /****************************/
    /*CSetupDevice* setupDevice = new CSetupDevice(core::dimension2d<u32>(800,600));
	if (!setupDevice) {
		printf("Failed setupDevice creation\n");
		return 1;
	}

	gui::IGUIEnvironment* setupGUI = setupDevice->getGUIEnvironment();
	populateSetupWindow(setupDevice);

	if (setupDevice->execute()) { // user closed the window... they don't want to play my game :'(
		delete setupDevice;
		setupDevice = NULL;
		setupGUI = NULL;
		return 0;
	}

	/**delete setupDevice; // Borrar la ventana no se ejecuta el bucle???????? **/
	/*setupDevice = NULL;
	setupGUI = NULL;*/

	/****************************/
    Scene scene;

    // Preguntamos por los parametros de la red
    cout << "//////////////////////////////////////////////\n";
    cout << "// Lab21\n";
    cout << "//////////////////////////////////////////////\n";
    cout << "// Selecciona tipo de partida y pulsa intro:\n";
    std::string type;
    cout << "// un solo jugador(1) o multijugador (2) [2 por defecto]: ";
    getline(cin, type);
    if (type!="1") type="2";

    NetInstance->open(&scene, (type=="2"));  // Inicializar motor de red
    cout << "//\n// Buscando servidores ";
    if(NetInstance->searchForServers())
    {
        cout << "\n//\n//Servidores de partidas disponibles:\n";
        std::vector<std::string>* servers = NetInstance->getServers();

        for(unsigned int i=0; i<servers->size(); i++)
            cout << "//  ("<<i<<") " << servers->at(i) << "\n";

        cout << "// Seleccione el numero de servidor de partidas [0] por defecto]: ";

        std::string ip;
        getline(cin, ip);

        NetInstance->connectToServer(atoi(ip.c_str()));

        if (NetInstance->getConnectionFailed())
        {
            cout << "No se encuentra el servidor " << ip << ", se inicia el juego en modo 1 jugador.\n";
            cout << "Presione intro para continuar. ";
            //getchar();
        }
        else if (NetInstance->getConnectionRejected())
        {
            NetInstance->setMultiplayer(false);
            cout << "No se puede acceder a la partida seleccionada. Partida llena o empezada, se inicia el juego en modo 1 jugador.\n";
            cout << "Presione intro para continuar. ";
            //getchar();
        }
        else
        {
            std::string seleccion;
            // Esperamos por las partidas
            int i=0;
            while (i<5 && !NetInstance->getGamesSearched())
            {
                usleep(40000);
                NetInstance->update();
                i++;
            }

            cout << "//  (0) Crear una nueva partida.\n";

            std::vector<std::string>* gamesIP = NetInstance->getGamesIP();
            for(unsigned int j=0; j<gamesIP->size(); j++)
                cout << "//  ("<<j+1<<") Unirse a " << gamesIP->at(j) << "\n";

            cout << "// Selecciona partida: ";
            getline(cin, seleccion);

            NetInstance->connectToGame(atoi(seleccion.c_str()));
        }
    }



	GEInstance->init();  // Inicializar motor gr�fico

    // Creaci�n de jugador
    Player* mainPlayer = GEInstance->createMainPlayer();
    mainPlayer->setPosition(dwe::vec3f(140-((NetInstance->getParticipantOrder()-1)*30),24,-80));
    mainPlayer->setLife(100);
    World->setMainPlayer(mainPlayer);
    cout << "Barra de vida: " << mainPlayer->getLife() << endl;


    // Creaci�n de escenario
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
    entities[1]=GEInstance->createDoor(3, false, 170, 0, 0); // false
    sector[0]=entities[1];


    // Generadores
    entities[2]=GEInstance->createGenerator(0, false, -50, 0, -50); // false
    ((Generator*)entities[2])->setSector(sector, 1);

    // Llaves
    MagnetKey *llave=GEInstance->createMagnetKey(0, 50, 0, 350);
    bool llaveCogida=false;

    // SpeedBoost
    scene.createSpeedBoost(210, 10, 10);
    scene.createSpeedBoost(100, 10, 10);

    // Medkit
    scene.createMedkit(400, 10, 0);
    scene.createMedkit(350, 10, 0);


//////
  // Llaves
    //Medkit *prueba1=GEInstance->createMedkit( 400, 0, 0);

//
  //dwe::Node* prueba = GEInstance->createNode("media/bullet/speed"); //ESTAS SON LAS BUENAS
	//prueba->setPosition(dwe::vec3f(400,0,0));



    // Triggers -> 0 Door, 1 Generator
    triggers[0]=GEInstance->createTrigger(0, 43.5, 0, 135.9);
    triggers[1]=GEInstance->createTrigger(0, 170, 0, 0);
    triggers[2]=GEInstance->createTrigger(1, -50, 0, -50);


    ////////////////////////////////
    // Enemigos
    ////////////////////////////////

    // Creaci�n de enemigo Humanoide
    Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
    //enemyHumanoid->setPosition(dwe::vec3f(43.5,24,-100));
    enemyHumanoid->setPosition(dwe::vec3f(400,24,100));
    enemyHumanoid->setRotation(dwe::vec3f(0, 90.f, 0));

    // Creaci�n de enemigo Dog
    Dog* enemyDog = GEInstance->createEnemyDog();
    enemyDog->setPosition(dwe::vec3f(-50,-170,100)); // No est� centrado :(



    //Creaci�n fov
    dwe::Node* fovnode = GEInstance->createNode("media/fov");
    //fovnode->setMaterialFlag(EMF_WIREFRAME, true);
    fovnode->setPosition(enemyHumanoid->getPosition());
    fovnode->setRotation(enemyHumanoid->getRotation());

   // dwe::Node* prueba = GEInstance->createNode("media/medkit/medkit"); //ESTAS SON LAS BUENAS
    //prueba->setPosition(dwe::vec3f(400,0,0));

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
    //CAMERA (nodo padre, posici�n, directi�n)
    ICameraSceneNode* camera1 = GEInstance->getSMGR()->addCameraSceneNode(0,  vector3df(0,0,0), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
    GEInstance->getSMGR()->setActiveCamera(camera1); //Activar c�mara


    //Creaci�n de objeto perception
    Perception* percep = new Perception();
    Pathplanning* pathp = new Pathplanning();



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
    scene.createProjectile(dwe::vec3f(1.0, 1.0, 1.0), 0.5);
    scene.deleteProjectile(0);
    //rmmEnd


    // Esperamos conexion de los demas jugadores
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

    float timeStamp = World->getTimeElapsed();
    float deltaTime;
    float timeLastProjectil = 0;


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

        deltaTime = World->getTimeElapsed() - timeStamp;
        timeStamp = World->getTimeElapsed();

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

        // Actualizamos f�sicas box2d
        World->step(deltaTime);
        World->clearForces();


        // comprobamos si dispara
        if((World->getTimeElapsed() - timeLastProjectil)> 200 && GEInstance->receiver.isLeftButtonPressed()){
            NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, mainPlayer->getPosition(), mainPlayer->getRotation().y); // Enviamos mensaje para crear projectil

            scene.createProjectile(mainPlayer->getPosition(), mainPlayer->getRotation().y);
            timeLastProjectil = World->getTimeElapsed();
        }


        mainPlayer->update(); //Posici�n actualizada de Irrlicht Player
        scene.updateProjectiles();
        scene.updateConsumables(mainPlayer);

        for(int cont=0; cont<NUM_ENTITIES; cont++)
            entities[cont]->update();



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
                llave = 0;
            }
        }


        // TriggerSystem
        for(int i=0; i<3; i++)
            if(mainPlayer->getNode()->intersects(triggers[i]->getNode()->getNode()))
            {
                if(GEInstance->receiver.isKeyDown(KEY_SPACE))
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

        //percep->senses(mainPlayer,enemyHumanoid,fovnode,num);  //llamamos a percepcion

        NetInstance->update();





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
    }

    delete bjoint;

    NetInstance->close();

	return 0;
}


