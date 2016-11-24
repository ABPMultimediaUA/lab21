#include <iostream>
#include <Box2D/Box2D.h>
#include <FachadeDireEngine.h>
#include "NetGame.h"
#include "Mono.h"

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
	fde::Graphics graphics;
	graphics.init(appReceiver);

	// Motor de red
    netGame = new dwn::NetGame();
    netGame->open(&graphics);


	Mono* mono = graphics.createMono("mono");
	mono->netGame = netGame;
	netGame->addNetObject(mono);

	//fde::Node* bot = graphics.createNode("bot");
	fde::Node* suelo = graphics.createNode("suelo");
	fde::Node* paredes = graphics.createNode("paredes");

	while(graphics.isRunning())
	{
	    //if (graphics.isWindowActive())
        //{
            fde::vec3f m(0.0f);

            if(appReceiver->isKeyDown(KEY_ESCAPE))
            {
                graphics.close();
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

            mono->move(m);

            graphics.draw();
        //}
        //else
        {
          //  graphics.yield();
        }

        netGame->update();
	}

	netGame->close();

	return 0;
}


