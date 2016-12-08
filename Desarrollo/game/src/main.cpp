#include <iostream>
#include <Box2D/Box2D.h>
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

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Box2D
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -1.0f);


    // Illricht
    AppReceiver* appReceiver = new AppReceiver();
	GEInstance->init(appReceiver);

	// Motor de red
    NetInstance->open();

    // Creación de jugador
	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->setPosition(dwe::vec3f(0,24,90));

    // Creación de escenario
	dwe::Node* suelo = GEInstance->createNode("media/suelo");
	dwe::Node* paredes = GEInstance->createNode("media/paredes");
	suelo->setPosition(dwe::vec3f(0,0,0));
	paredes->setPosition(dwe::vec3f(0,35,0));
    //door *puerta=new door(0,0,0,false);


    // Creación de enemigo Humanoide
	Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
	enemyHumanoid->setPosition(dwe::vec3f(0,24,-70));

    //Creación de objeto pathplanning
    Pathplanning* pathp = new Pathplanning();
    float num=10.0;//para cambiar de sigilo a rapido
    bool danyo=false;

	while(GEInstance->isRunning())
	{
//	    if (GEInstance->isWindowActive())
//        {
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
                    m.z -= 0.2;
                    r.y = 90.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_LEFT))
                {
                    m.z += 0.2;
                    r.y = -90.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_UP))
                {
                    m.x += 0.2;
                    r.y = 0.f;

                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_DOWN))
                {
                    m.x -= 0.2;
                    r.y = 180.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_KEY_A))//prototipo de disparo
                {
                    danyo=true;//ponemos el bool de danyo en el npc a true
                }
                else
                {
                    mainPlayer->setAnimation(dwe::eAnimStand);
                }
            }

            mainPlayer->setPosition(m);
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


