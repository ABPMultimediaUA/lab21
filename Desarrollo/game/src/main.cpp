#include <iostream>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GraphicsEngine.h>

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

#include "Selector.h"
#include "Sequence.h"

#include "Pathplanning.h"
#include "Perception.h"

#include "CheckIfDoorIsOpenTask.h"
#include "ApproachDoorTask.h"
#include "OpenDoorTask.h"
#include "WalkThroughDoorTask.h"
#include "CloseDoorTask.h"

#include "EntityPhysics.h"

#include "ScenaryElement.h"

#define nEntities 3


float angulo;


dwe::vec3f de2Da3D(int x2d, int y2d, dwe::vec3f r){
	float centerScreenX = 400;
	float centerScreenY = 300;
	dwe::vec3f v(x2d - centerScreenX,y2d - centerScreenY,0);
    dwe::vec3f u(1,0,0);

	float numerador     = (u.x*v.x) + (u.y*v.y);
	float denominador   = sqrt( pow(u.x,2) + pow(u.y,2) ) * sqrt( pow(v.x,2) + pow(v.y,2) );
	angulo = acos(numerador/denominador) * (180/M_PI);

	if(y2d<centerScreenY){
        r.y = -angulo;
	}else{
        r.y = angulo;
        angulo=-angulo;
    }

    return(r);
}



///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Inicializar motor gráfico
	GEInstance->init();

	// Inicializar motor de red
    NetInstance->open();


    // Creación de jugador
	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->setPosition(dwe::vec3f(120,24,0));


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
    entities=new Entity*[nEntities];
    sector=new Entity*[1];

    // Puertas
    entities[0]=GEInstance->createDoor(0, true, 43.5, 36.3, 135.9);
    entities[1]=GEInstance->createDoor(3, false, 170, 36.3, 0);
    sector[0]=entities[1];

    //((Door*)entities[0])->setIsOpening();

    // Generadores
    entities[2]=GEInstance->createGenerator(0, false, -50, 0, -50);
    ((Generator*)entities[2])->setSector(sector, 1);

    //Llaves
    MagnetKey *llave=GEInstance->createMagnetKey(0, 50, 0, 350);
    bool llaveCogida=false;

    ////////////////////////////////
    // Enemigos
    ////////////////////////////////
    // Creación de enemigo Humanoide
	Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
	//enemyHumanoid->setPosition(dwe::vec3f(-70,24,0));
	enemyHumanoid->setPosition(dwe::vec3f(43.5,24,-100));
	enemyHumanoid->setRotation(dwe::vec3f(0, 270.f, 0));


	// Creación de enemigo Dog
	Dog* enemyDog = GEInstance->createEnemyDog();
	enemyDog->setPosition(dwe::vec3f(-50,-170,100)); // No está centrado :(
	//enemyDog->setPosition(dwe::vec3f(0,-300,-40));




    //Creación fov
    dwe::Node* fovnode = GEInstance->createNode("media/fov");
    //fovnode->setMaterialFlag(EMF_WIREFRAME, true);
    fovnode->setPosition(enemyHumanoid->getPosition());
    fovnode->setRotation(enemyHumanoid->getRotation());


	// Creacion objeto Proyectil
	Projectile *projectile = 0;



	//////////////////////////////////////////
    //CAMERA (nodo padre, posición, directión)
	ICameraSceneNode* camera1 = GEInstance->getSMGR()->addCameraSceneNode(0,  vector3df(0,200,-100), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	GEInstance->getSMGR()->setActiveCamera(camera1); //Activar cámara

    /////////////////////////////////////////////////////////////////////////////////////////////
    ITimer* timer = GEInstance->getDevice()->getTimer(); //METIDO DEL DEBUG DRAW DE BOX2D...

    f32 timeStamp = timer->getTime();
    f32 deltaTime = timer->getTime() - timeStamp;
    //TIEMPO
    /////////////////////////////////////////////////////////////////////////////////////////////


    //Creación de objeto perception
    Perception* percep = new Perception();
    float num;//para cambiar de sigilo a rapido
    /*************************** BEHAVIOR TREE **********************************/


    /**** Special nodes ****/

	Selector* selector1 = new Selector;

	Sequence *sequence1 = new Sequence;
    Sequence *sequence2 = new Sequence;

    /**** Tasks ****/

    CheckIfDoorIsOpenTask* checkOpen = new CheckIfDoorIsOpenTask ((Door*)entities[0]);
    ApproachDoorTask* approach = new ApproachDoorTask (enemyHumanoid, (Door*)entities[0]);
	OpenDoorTask* open = new OpenDoorTask ((Door*)entities[0]);
	WalkThroughDoorTask* through = new WalkThroughDoorTask (enemyHumanoid, (Door*)entities[0]);
	CloseDoorTask* close = new CloseDoorTask ((Door*)entities[0]);


    /**** Creating the tree ****/

    selector1->addChild(sequence1);
    selector1->addChild(sequence2);

    sequence1->addChild(checkOpen);
    sequence1->addChild(approach);
    sequence1->addChild(through);
    sequence1->addChild(close);

    sequence2->addChild(approach);
    sequence2->addChild(open);
    sequence2->addChild(through);
    sequence2->addChild(close);




    //////////////////////////////////////////////////////////////////

    //rmm Cheat: la primera vez que creo el projectile va muy lento
    projectile=GEInstance->createProjectile(mainPlayer->getPosition(), angulo);
    delete projectile;
    projectile = 0;
    //rmmEnd

	while(GEInstance->isRunning())
	{
        if(GEInstance->receiver.isKeyDown(KEY_ESCAPE))
        {
            GEInstance->close();
            return 0;
        }

        // Run Behavior Tree
        selector1->run();
        //fovnode->setPosition(enemyHumanoid->getPosition());


        //prototipo de disparo
        //if(GEInstance->receiver.isKeyDown(KEY_KEY_F)){danyo=true;}//ponemos el bool de danyo en el npc a true

        mainPlayer->readEvents();

        //Calcular rotacion player - con MOUSE
        if(GEInstance->receiver.getCursorX()>=0 && GEInstance->receiver.getCursorY()>=0){
            mainPlayer->setRotation(
                de2Da3D(GEInstance->receiver.getCursorX(),
                        GEInstance->receiver.getCursorY(),
                        mainPlayer->getRotation()));
        }


        // Actualizamos físicas box2d
        deltaTime = timer->getTime()-timeStamp; timeStamp=timer->getTime();
        World->step(deltaTime);
        World->clearForces();

        // comprobamos si dispara
        if(projectile==0 && GEInstance->receiver.isLeftButtonPressed()){
            projectile=GEInstance->createProjectile(mainPlayer->getPosition(), angulo);
        }

        //Posición actualizada de Irrlicht Player
        mainPlayer->update();

        for(int cont=0; cont<nEntities; cont++)
        {
            entities[cont]->update();
        }

        if(projectile!=0)
        {
            projectile->update();
            if (projectile->getCollides())
            {
                delete projectile;
                projectile = 0;
            }
        }

        //update camera target
        GEInstance->getSMGR()->getActiveCamera()->setTarget(vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
        //update camera position
        float getCamPosZ = GEInstance->getSMGR()->getActiveCamera()->getPosition().Z;
        float setCamPosZ;

        float cameraDist = getCamPosZ - mainPlayer->getPosition().z;
        cameraDist = fabsf(cameraDist);
        //cout << "cameraDist: " << cameraDist << endl;
        if(getCamPosZ>-300.0f){
            if(cameraDist<100.f){
                setCamPosZ = mainPlayer->getPosition().z-100;
            }else if(cameraDist>200.0f){
                setCamPosZ = mainPlayer->getPosition().z-200;
            }
        }else{
            if(cameraDist>200.0f){
                setCamPosZ = mainPlayer->getPosition().z-200;
            }

            //reajuste... cuando estoy cerca de una pared final encima de la camara
            if(cameraDist<10.0f){
                setCamPosZ = mainPlayer->getPosition().z-10;
            }
        }
        GEInstance->getSMGR()->getActiveCamera()->setPosition(vector3df(mainPlayer->getPosition().x,200,setCamPosZ));

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

        //llamamos a percepcion
        percep->senses(mainPlayer,enemyHumanoid,fovnode,num);

        NetInstance->update();
	}

	NetInstance->close();

	return 0;
}


