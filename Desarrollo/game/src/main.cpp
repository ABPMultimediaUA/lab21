#include <iostream>
#include <Box2D/Box2D.h>
#include <GraphicsEngine.h>
#include "NetGame.h"
#include "Player.h"
#include "Whole.h"

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


	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->setPosition(dwe::vec3f(0,24,90));


	dwe::Node* suelo = GEInstance->createNode("media/suelo");
	dwe::Node* paredes = GEInstance->createNode("media/paredes");
	paredes->setPosition(dwe::vec3f(0,35,0));

	Whole* enemyWhole = GEInstance->createEnemyWhole();
	enemyWhole->setPosition(dwe::vec3f(0,24,-70));

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
                    m.z -= 0.02;
                    r.y = 90.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_LEFT))
                {
                    m.z += 0.02;
                    r.y = -90.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_UP))
                {
                    m.x += 0.02;
                    r.y = 0.f;

                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_DOWN))
                {
                    m.x -= 0.02;
                    r.y = 180.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
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
	}

	NetInstance->close();

	return 0;
}


