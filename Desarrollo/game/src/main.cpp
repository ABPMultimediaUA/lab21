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
#include "Projectile.h"

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
#include "World.h"

//#define speed 20.0f
#define M_PI 3.14159265358979323846

float angulo;


dwe::vec3f de2Da3D(float x2d, float y2d, dwe::vec3f r){
	//cout << "X:" <<  x2d << "  ...  Y:" <<  y2d << endl;
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
    // Illricht
    AppReceiver* appReceiver = new AppReceiver();
	GEInstance->init(appReceiver);


	// Motor de red
    NetInstance->open();


    // Creación de jugador
	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->setPosition(dwe::vec3f(50,24,50));


    // Creación de escenario
	dwe::Node* suelo = GEInstance->createNode("media/suelo");
	dwe::Node* paredes = GEInstance->createNode("media/paredes");
	suelo->setPosition(dwe::vec3f(0,0,0));
	paredes->setPosition(dwe::vec3f(0,35,0));

    Door *puerta=GEInstance->createDoor();
    puerta->setActive();
    //puerta->setIsOpening();

    // Creación de enemigo Humanoide
	Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
	enemyHumanoid->setPosition(dwe::vec3f(-70,24,0));

    //Creación fov
    dwe::Node* fovnode = GEInstance->createNode("media/fov");
    //fovnode->setMaterialFlag(EMF_WIREFRAME, true);
    fovnode->setPosition(enemyHumanoid->getPosition());


	// Creacion objeto Proyectil
	Projectile *p;
	bool disparado=false; // Control

	// Creación de enemigo Dog
	Dog* enemyDog = GEInstance->createEnemyDog();
	enemyDog->setPosition(dwe::vec3f(-100,-170,100)); /** No está centrado :( **/
	//enemyDog->setPosition(dwe::vec3f(0,-300,-40));


    //BOX2D
	EntityPhysics* bwBox = new EntityPhysics();
    bwBox->createStaticBox(vector2d<s32>(0,-70));
	cout << "YES2 \n";

	 //CAMERA (nodo padre, posición, directión)
	ICameraSceneNode* camera1 = GEInstance->getSMGR()->addCameraSceneNode(0,  vector3df(0,200,-100), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	ICameraSceneNode* camera2 = GEInstance->getSMGR()->addCameraSceneNode(0, vector3df(0,100,-200), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	ICameraSceneNode* camera3 = GEInstance->getSMGR()->addCameraSceneNode(0, vector3df(-50,150,-100), vector3df(mainPlayer->getPosition().x,mainPlayer->getPosition().y,mainPlayer->getPosition().z));
	GEInstance->getSMGR()->setActiveCamera(camera1); //Activar cámara

/////////////////////////////////////////////////////////////////////////////////////////////
    ITimer* timer = GEInstance->getDevice()->getTimer(); //METIDO DEL DEBUG DRAW DE BOX2D...

    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;
    //TIEMPO
/////////////////////////////////////////////////////////////////////////////////////////////


    //Creación de objeto perception
    Perception* percep = new Perception();
    float num;//para cambiar de sigilo a rapido
    bool danyo=false;
    float speed=20.0f;
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

            /* Run Behavior Tree */
            //selector1->run();

            /* Run State Machine */
          //  enemyDog->Update();


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
                if(appReceiver->isKeyDown(KEY_KEY_D)){
                    speedX = speed;
                }else if(appReceiver->isKeyDown(KEY_KEY_A)){
                    speedX = -speed;
                }

                //Hacia delante o hacia detras
                if(appReceiver->isKeyDown(KEY_KEY_W)){
                    speedZ = speed;
                }else if(appReceiver->isKeyDown(KEY_KEY_S)){
                    speedZ = -speed;
                }

                //prototipo de disparo
                if(appReceiver->isKeyDown(KEY_KEY_F)){danyo=true;}//ponemos el bool de danyo en el npc a true

                if(appReceiver->isKeyDown(KEY_LSHIFT)) {
                        speed=5.0f;
                        num=speed;
                }
                else{
                        speed=20.0f;
                        num=speed;
                }


                //Animacion del player
                if(speedX!=0 || speedZ!=0){
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }else{
                    mainPlayer->setAnimation(dwe::eAnimStand);
                }

                mainPlayer->setVelocity(dwe::vec3f(speedX, 0, speedZ));

                // DISPARO
                //cout<<angulo<<endl;
                if(appReceiver->isKeyDown(KEY_SPACE)){
                    int origen[2];
                    origen[0]=m.x;
                    origen[1]=m.z;
                    p=GEInstance->createProjectile(origen, angulo);
                    disparado=true;
                }

            }

            //Calcular rotacion player - con MOUSE
            if(appReceiver->getCursorX()>=0 && appReceiver->getCursorY()>=0){
                r = de2Da3D(appReceiver->getCursorX(),appReceiver->getCursorY(), r);
            }

            DeltaTime = timer->getTime() - TimeStamp;
            TimeStamp = timer->getTime();
            // Instruct the world to perform a single step of simulation.
            // It is generally best to keep the time step and iterations fixed.
            WInstance->step(DeltaTime);
            // Clear applied body forces. We didn't apply any forces, but you
            // should know about this function.
            WInstance->clearForces();

            //Posición actualizada de Irrlicht Player
            mainPlayer->update();
            mainPlayer->setRotation(r);
            puerta->update();
            if(disparado)
                p->update();

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
        //llamamos a percepcion
        percep->senses(mainPlayer,enemyHumanoid,fovnode,num);

        NetInstance->update();


	}

	NetInstance->close();

	return 0;
}


