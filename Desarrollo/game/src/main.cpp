#include <iostream>
#include <Box2D/Box2D.h>
#include <FachadeDireEngine.h>
#include "NetGame.h"
#include "Mono.h"
#include "Player.h"

dwn::NetGame* netGame;

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Box2D
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);



    // Illricht
    AppReceiver* appReceiver = new AppReceiver();
	GEInstance->init(appReceiver);

	// Motor de red
    netGame = new dwn::NetGame();
    netGame->open();


	//Mono* mono = GEInstance->createMono("mono");
	//mono->netGame = netGame;
	//netGame->addNetObject(mono);
	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->netGame = netGame;
	netGame->addNetObject(mainPlayer);

	//fde::Node* bot = graphics.createNode("bot");
	dwe::Node* suelo = GEInstance->createNode("suelo");
	dwe::Node* paredes = GEInstance->createNode("paredes");

	while(GEInstance->isRunning())
	{
//	    if (GEInstance->isWindowActive())
//        {
            dwe::vec3f m(0.0f);
            m = mainPlayer->getPosition();

            if(appReceiver->isKeyDown(KEY_ESCAPE))
            {
                GEInstance->close();
                return 0;
            }
            else
            {
                if(appReceiver->isKeyDown(KEY_RIGHT))
                    m.z -= 0.005;
                else if(appReceiver->isKeyDown(KEY_LEFT))
                    m.z += 0.005;
                else if(appReceiver->isKeyDown(KEY_UP))
                    m.x += 0.005;
                else if(appReceiver->isKeyDown(KEY_DOWN))
                    m.x -= 0.005;
            }

            mainPlayer->setPosition(m);

            GEInstance->draw();
//        }
//        else
//        {
//            GEInstance->yield();
//        }

        netGame->update();
	}

	netGame->close();

	return 0;
}


