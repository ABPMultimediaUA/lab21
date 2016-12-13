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

#include "door.h"
#include "Pathplanning.h"

#include "EntityPhysics.h"
#include "World.h"

#define speed 20.0f



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
	mainPlayer->setPosition(dwe::vec3f(0,24,90));
    dwe::vec3f pos= mainPlayer->getPosition();
    cout << "POS: X = " << pos.x << " ... Y = " << pos.y << " ... Z = " << pos.z << endl;
    //BOX2D
    EntityPhysics* bwPlayer = new EntityPhysics();
    bwPlayer->createDynPhyEntity(world,vector2d<s32>(0,90), GEInstance->getDevice());
	cout << "YES \n";

	////////////////////

    // Creación de escenario
	dwe::Node* suelo = GEInstance->createNode("media/suelo");
	dwe::Node* paredes = GEInstance->createNode("media/paredes");
	suelo->setPosition(dwe::vec3f(0,0,0));
	paredes->setPosition(dwe::vec3f(0,35,0));
    //door *puerta=new door(0,0,0,false);

    // Creación de enemigo Humanoide
	Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
	enemyHumanoid->setPosition(dwe::vec3f(0,24,-70));

    //BOX2D
	EntityPhysics* bwBox = new EntityPhysics();
    bwBox->createStaticBox(world,vector2d<s32>(0,-70), GEInstance->getDevice());
	cout << "YES2 \n";

	 //CAMERA (nodo padre, posición, directión)
	ICameraSceneNode* camera1 = GEInstance->getSMGR()->addCameraSceneNode(0, vector3df(0,200,-100), vector3df(0,5,0));
	ICameraSceneNode* camera2 = GEInstance->getSMGR()->addCameraSceneNode(0, vector3df(0,100,-200), vector3df(0,5,0));
	ICameraSceneNode* camera3 = GEInstance->getSMGR()->addCameraSceneNode(0, vector3df(-50,150,-100), vector3df(0,5,0));
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
    u32 then = GEInstance->getDevice()->getTimer()->getTime();
/////////////////////////////////////////////////////////////////////////////////////////////

    //Creación de objeto pathplanning
    Pathplanning* pathp = new Pathplanning();
    float num=10.0;//para cambiar de sigilo a rapido
    bool danyo=false;

    ///////////////////////////////////  BUCLE
	while(GEInstance->isRunning())
	{
//	    if (GEInstance->isWindowActive())
//        {

           // position2d<s32> coord = position2d<s32>(0,0);
            //core::position2di cursor = core::position2di(appReceiver->OnEvent(const SEvent& rotating),0);
                                                         //event.MouseInput.X, event.MouseInput.Y);
            //cout << "Mouse at 2D coordinates: " << cursor.X << "," << cursor.Y << endl;
/////////////////////////////////////////////////////////////////////////////////////////////
            //Calcular DELTA TIME ( dt )
            const u32 now = GEInstance->getDevice()->getTimer()->getTime();
            //const f32 dt = (f32) (now - then) / 1000.f;
            const f32 MOVEMENT_SPEED = 10.0f;
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
                if(appReceiver->isKeyDown(KEY_RIGHT))
                {
                    bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(speed,0.0));
                    r.y = 0.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_LEFT))
                {
                    bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(-speed,0.0));
                    r.y = 180.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_UP))
                {
                    bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(0.0,speed));
                    r.y = -90.f;

                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_DOWN))
                {
                    bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(0.0,-speed));
                    r.y = 90.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_KEY_A))//prototipo de disparo
                {
                    danyo=true;//ponemos el bool de danyo en el npc a true
                }
                else
                {
                    bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(0.0,0.0));
                    mainPlayer->setAnimation(dwe::eAnimStand);
                }
            }

            //node->setPosition(nodePos); //Cambio de posición
            then = now; //Actualizar TIMEPO

            DeltaTime = timer->getTime() - TimeStamp;
            TimeStamp = timer->getTime();
            // Instruct the world to perform a single step of simulation.
            // It is generally best to keep the time step and iterations fixed.
            world.Step(DeltaTime*timeStep, velocityIterations, positionIterations);
            // Clear applied body forces. We didn't apply any forces, but you
            // should know about this function.
            world.ClearForces();

            bwPlayer->updatePhysics(); //UPDATE de mi player BOX2D
            //cout << "PLAYER POS: X=" << bwPlayer->getBwBody()->GetPosition().x << "... Y=" << bwPlayer->getBwBody()->GetPosition().y << endl;
            //Posición actualizada de Irrlicht Player
            //mainPlayer->setPosition(dwe::vec3f(0,24,90));
            mainPlayer->setPosition(dwe::vec3f(bwPlayer->getBwBody()->GetPosition().x,24,bwPlayer->getBwBody()->GetPosition().y));


            //mainPlayer->setPosition(m);
            mainPlayer->setRotation(r);


            GEInstance->draw();
//        }
//        else
//        {
//            GEInstance->yield();
//        }

        NetInstance->update();
        ///////PARTE DE PATHPLANNING
        pathp->behaviour(mainPlayer, enemyHumanoid, num, danyo);

        //////////////////////////////////////

	}

	NetInstance->close();

	return 0;
}


