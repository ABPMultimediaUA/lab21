#include <iostream>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GraphicsEngine.h>

#include "NetGame.h"
#include "Player.h"
#include "Bat.h"
#include "Mother.h"
#include "Guardian.h"
#include "Legless.h"
#include "Dog.h"
#include "Humanoid.h"

#include "Door.h"
#include "Pathplanning.h"

#include "Selector.h"
#include "Sequence.h"

#include "CheckIfDoorIsOpenTask.h"
#include "ApproachDoorTask.h"
#include "OpenDoorTask.h"
#include "WalkThroughDoorTask.h"
#include "CloseDoorTask.h"
#include "Pathplanning.h"

#include "EntityPhysics.h"
#include "World.h"

#define speed 20.0f
#define M_PI 3.14159265358979323846


dwe::vec3f de2Da3D(float x2d, float y2d, dwe::vec3f r){
	//cout << "X:" <<  x2d << "  ...  Y:" <<  y2d << endl;
	float centerScreenX = 400;
	float centerScreenY = 300;
	dwe::vec3f v(x2d - centerScreenX,y2d - centerScreenY,0);
    dwe::vec3f u(1,0,0);

	float numerador     = (u.x*v.x) + (u.y*v.y);
	float denominador   = sqrt( pow(u.x,2) + pow(u.y,2) ) * sqrt( pow(v.x,2) + pow(v.y,2) );
	float angulo = acos(numerador/denominador) * (180/M_PI);

	if(y2d<centerScreenY){
        r.y = -angulo;
	}else{
        r.y = angulo;
    }

    return(r);
}



///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Box2D
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    // Illricht
    AppReceiver* appReceiver = new AppReceiver();
	GEInstance->init(appReceiver);

	// Motor de red
    NetInstance->open();

    // Creación de jugador
	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->setPosition(dwe::vec3f(0,24,0));
    dwe::vec3f pos= mainPlayer->getPosition();
    cout << "POS: X = " << pos.x << " ... Y = " << pos.y << " ... Z = " << pos.z << endl;
    //BOX2D
    EntityPhysics* bwPlayer = new EntityPhysics();
    bwPlayer->createDynPhyEntity(world,vector2d<s32>(0,0), GEInstance->getDevice());
	cout << "YES \n";

	////////////////////

    // Creación de escenario
	dwe::Node* suelo = GEInstance->createNode("media/suelo");
	dwe::Node* paredes = GEInstance->createNode("media/paredes");
	suelo->setPosition(dwe::vec3f(0,0,0));
	paredes->setPosition(dwe::vec3f(0,35,0));

    Door *puerta=GEInstance->createDoor();
    puerta->setPosition(dwe::vec3f(0,0,0));
    puerta->setActive();
//    puerta->setIsOpening();

    // Creación de enemigo Humanoide
	Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
	enemyHumanoid->setPosition(dwe::vec3f(-70,24,0));


	// Creación de enemigo Dog
	Dog* enemyDog = GEInstance->createEnemyDog();
	enemyDog->setPosition(dwe::vec3f(-100,-120,100)); /** No está centrado :( **/
	//enemyDog->setPosition(dwe::vec3f(0,-300,-40));
    //BOX2D
	EntityPhysics* bwBox = new EntityPhysics();
    bwBox->createStaticBox(world,vector2d<s32>(0,-70), GEInstance->getDevice());
	cout << "YES2 \n";

	 //CAMERA (nodo padre, posición, directión)
	ICameraSceneNode* camera1 = GEInstance->getSMGR()->addCameraSceneNode(0,  vector3df(0,200,-100), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	ICameraSceneNode* camera2 = GEInstance->getSMGR()->addCameraSceneNode(0, vector3df(0,100,-200), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	ICameraSceneNode* camera3 = GEInstance->getSMGR()->addCameraSceneNode(0, vector3df(-50,150,-100), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	GEInstance->getSMGR()->setActiveCamera(camera1); //Activar cámara

/////////////////////////////////////////////////////////////////////////////////////////////
    ITimer* timer = GEInstance->getDevice()->getTimer(); //METIDO DEL DEBUG DRAW DE BOX2D...

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 250.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;
    //TIEMPO
/////////////////////////////////////////////////////////////////////////////////////////////


    //Creación de objeto pathplanning
    Pathplanning* pathp = new Pathplanning();
    float num=10.0;//para cambiar de sigilo a rapido
    bool danyo=false;

    /*************************** BEHAVIOR TREE **********************************/


    /**** Special nodes ****/

	Selector* selector1 = new Selector;

	Sequence *sequence1 = new Sequence;
    Sequence *sequence2 = new Sequence;


    /**** Tasks ****/

    CheckIfDoorIsOpenTask* checkOpen = new CheckIfDoorIsOpenTask (puerta);
    ApproachDoorTask* approach = new ApproachDoorTask (enemyHumanoid, puerta);
	OpenDoorTask* open = new OpenDoorTask (puerta);
	WalkThroughDoorTask* through = new WalkThroughDoorTask (enemyHumanoid, puerta);
	CloseDoorTask* close = new CloseDoorTask (puerta);


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



    /****************************************************************************/

    ///////////////////////////////////  BUCLE
	while(GEInstance->isRunning())
	{

            selector1->run();


//	    if (GEInstance->isWindowActive())
//        {

           // position2d<s32> coord = position2d<s32>(0,0);
            //core::position2di cursor = core::position2di(appReceiver->OnEvent(const SEvent& rotating),0);
                                                         //event.MouseInput.X, event.MouseInput.Y);
            //cout << "Mouse at 2D coordinates: " << cursor.X << "," << cursor.Y << endl;
/////////////////////////////////////////////////////////////////////////////////////////////

            //CAMBIO DE CAMARA
            if (appReceiver->isKeyDown(KEY_KEY_1)){
                printf("- Camara 1 \n");
                GEInstance->getSMGR()->setActiveCamera(camera1);
            }else if(appReceiver->isKeyDown(KEY_KEY_2)){
                printf("- Camara 2 \n");
                GEInstance->getSMGR()->setActiveCamera(camera2);
            }else if(appReceiver->isKeyDown(KEY_KEY_3)){
                printf("- Camara 3 \n");
                GEInstance->getSMGR()->setActiveCamera(camera3);
            }

            dwe::vec3f m(0.0f);
            m = mainPlayer->getPosition();

            dwe::vec3f r(0.0f);
            r = mainPlayer->getRotation();


            if(appReceiver->isKeyDown(KEY_ESCAPE))
            {
                GEInstance->close();
                return 0;
            }
            else
            {
                float speedX = 0.0f;
                float speedZ = 0.0f;

                //Derecha o izquierda
                if(appReceiver->isKeyDown(KEY_RIGHT)){
                    speedX = speed;
                }else if(appReceiver->isKeyDown(KEY_LEFT)){
                    speedX = -speed;
                }

                //Hacia delante o hacia detras
                if(appReceiver->isKeyDown(KEY_UP)){
                    speedZ = speed;
                }else if(appReceiver->isKeyDown(KEY_DOWN)){
                    speedZ = -speed;
                }

                //prototipo de disparo
                if(appReceiver->isKeyDown(KEY_KEY_A)){danyo=true;}//ponemos el bool de danyo en el npc a true

                //Animacion del player
                if(speedX!=0 || speedZ!=0){
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }else{
                    mainPlayer->setAnimation(dwe::eAnimStand);
                }

                bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(speedX,speedZ)); //MOVIMIENTO DEL BOX2D PLAYER

            }

            //Calcular rotacion player - con MOUSE
            if(appReceiver->getCursorX()>=0 && appReceiver->getCursorY()>=0){
                r = de2Da3D(appReceiver->getCursorX(),appReceiver->getCursorY(), r);
            }

            DeltaTime = timer->getTime() - TimeStamp;
            TimeStamp = timer->getTime();
            // Instruct the world to perform a single step of simulation.
            // It is generally best to keep the time step and iterations fixed.
            world.Step(DeltaTime*timeStep, velocityIterations, positionIterations);
            // Clear applied body forces. We didn't apply any forces, but you
            // should know about this function.
            world.ClearForces();

            bwPlayer->updatePhysics(); //UPDATE de mi player BOX2D

            //Posición actualizada de Irrlicht Player
            mainPlayer->setPosition(dwe::vec3f(bwPlayer->getBwBody()->GetPosition().x,24,bwPlayer->getBwBody()->GetPosition().y)); //MOVIMIENTO DE IRRLICHT PLAYER
            mainPlayer->setRotation(r);
            puerta->update();

            //update camera target
            GEInstance->getSMGR()->getActiveCamera()->setTarget(vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
            //update camera position
            GEInstance->getSMGR()->getActiveCamera()->setPosition(vector3df(mainPlayer->getPosition().x,200,-100));


            GEInstance->draw();
//        }
//        else
//        {
//            GEInstance->yield();
//        }

        NetInstance->update();
        ///////PARTE DE PATHPLANNING
        //pathp->behaviour(mainPlayer, enemyHumanoid, num, danyo);

        //////////////////////////////////////

	}

	NetInstance->close();

	return 0;
}


