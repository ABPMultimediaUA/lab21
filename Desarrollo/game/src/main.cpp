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

#include "EntityPhysics.h"
#include "ScenaryElement.h"

#define nEntities 3

#define camDesvio 50
#define progresion 1.5f

#define centerScreenX 400
#define centerScreenY 300

float angulo;

dwe::vec3f de2Da3D(int x2d, int y2d, dwe::vec3f r){
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
    entities=new Entity*[nEntities];
    sector=new Entity*[1];
    triggers=new Trigger*[3];

    // Puertas
    entities[0]=GEInstance->createDoor(0, true, 43.5, 0, 135.9);
    entities[1]=GEInstance->createDoor(3, false, 170, 0, 0); // false
    sector[0]=entities[1];

    //((Door*)entities[0])->setIsOpening();

    // Generadores
    entities[2]=GEInstance->createGenerator(0, false, -50, 0, -50); // false
    ((Generator*)entities[2])->setSector(sector, 1);

    // Llaves
    MagnetKey *llave=GEInstance->createMagnetKey(0, 50, 0, 350);
    bool llaveCogida=false;

    // Triggers -> 0 Door, 1 Generator
    triggers[0]=GEInstance->createTrigger(0, 43.5, 0, 135.9);
    triggers[1]=GEInstance->createTrigger(0, 170, 0, 0);
    triggers[2]=GEInstance->createTrigger(1, -50, 0, -50);

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

    //Salud
	dwe::Node* first_aid = GEInstance->createNode("media/First_Aid_Med_Kit/FirstAidMedKit");
	first_aid->setPosition(dwe::vec3f(400,0,0));

	 //Pistola 1
	dwe::Node* gun_1 = GEInstance->createNode("media/Gun/Gun"); //ESTAS SON LAS BUENAS
	gun_1->setPosition(dwe::vec3f(400,10,100));

    //Pistola 2
	dwe::Node* gun_2 = GEInstance->createNode("media/Gun/Gun");   //ESTAS SON LAS BUENAS
	gun_2->setPosition(dwe::vec3f(220,10,100));

	//////////////////////////////////////////
    //CAMERA (nodo padre, posición, directión)
	ICameraSceneNode* camera1 = GEInstance->getSMGR()->addCameraSceneNode(0,  vector3df(0,0,0), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
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

            //para probar --- cuando disparo pierdo vida
            mainPlayer->setLife(mainPlayer->getLife()-10);
            cout << "CUIDADO!! si disparo pierdo vida. \n Vida actual: " << mainPlayer->getLife() << endl;
        }

        //Posición actualizada de Irrlicht Player
        mainPlayer->update();


        // Entities update
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
        //Desencuadre horizontal
        if(GEInstance->receiver.getCursorX()<50){
            if(tarLR>-camDesvio)
                tarLR-=progresion;
        }else if(GEInstance->receiver.getCursorX()>750){
            if(tarLR<camDesvio)
                tarLR+=progresion;
        }else{
            //Volver a centrar
            if(tarLR!=0)
                if(tarLR<0)
                    tarLR+=progresion;
                else
                    tarLR-=progresion;
            else
                tarLR = 0;
        }

        //Desencuadre vertical
        if(GEInstance->receiver.getCursorY()<50){
            if(tarUD<camDesvio)
                tarUD+=progresion;
        }else if(GEInstance->receiver.getCursorY()>550){
            if(tarUD>-camDesvio)
                tarUD-=progresion;
        }else{
            //Volver a centrar
            if(tarUD!=0)
                if(tarUD<0)
                    tarUD+=progresion;
                else
                    tarUD-=progresion;
            else
                tarUD = 0;
        }

        GEInstance->getSMGR()->getActiveCamera()->setTarget(vector3df(mainPlayer->getPosition().x+tarLR,mainPlayer->getPosition().y,mainPlayer->getPosition().z+tarUD));

        //update camera position
        float setCamPosZ = mainPlayer->getPosition().z-100; //editar la posición de la camara en ejeZ
        GEInstance->getSMGR()->getActiveCamera()->setPosition(vector3df(mainPlayer->getPosition().x+tarLR,250,setCamPosZ+tarUD));

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
        // TriggerSystem
        for(int i=0; i<3; i++)
        {
            if(mainPlayer->getNode()->intersects(triggers[i]->getNode()->getNode()))
            {
                if(GEInstance->receiver.isKeyDown(KEY_SPACE))
                {
                    //cout<<"TRI";
                    if(i==2){
                        if(mainPlayer->getMKey(((Generator*)entities[i])->getNum()))
                        {
                            //cout<<"GENE";
                            triggers[i]->triggered(entities[i]);
                        }

                    }
                    else if(i==0 || i==1)
                    {
                        //cout<<"DOOR";
                        triggers[i]->triggered(entities[i]);
                    }
                    //cout<<"GGERED"<<endl;
                }
            }
        }

        //llamamos a percepcion
        percep->senses(mainPlayer,enemyHumanoid,fovnode,num);

        NetInstance->update();
	}

	NetInstance->close();

	return 0;
}


