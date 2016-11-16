#include <iostream>
#include <Box2D/Box2D.h>
#include <FachadeDireEngine.h>
#include <AppReceiver.h>


int main()
{
    // Box2D
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);



    // Illricht
    AppReceiver* appReceiver = new AppReceiver();
	fde::Graphics graphics;
	graphics.init(appReceiver);

	fde::Node* mono = graphics.createNode("mono");


	while(graphics.isRunning())
	{
	    if (graphics.isWindowActive())
        {
            fde::vec3f pos(0.0f);

            if(appReceiver->isKeyDown(KEY_ESCAPE))
            {
                graphics.close();
                return 0;
            }
            else
            {
                if(appReceiver->isKeyDown(KEY_RIGHT))
                    pos.x += 0.02;
                if(appReceiver->isKeyDown(KEY_LEFT))
                    pos.x -= 0.02;
                if(appReceiver->isKeyDown(KEY_UP))
                    pos.y += 0.02;
                if(appReceiver->isKeyDown(KEY_DOWN))
                    pos.y -= 0.02;
            }

            mono->move(pos);

            graphics.draw();
        }
        else
        {
            graphics.yield();
        }
	}


	return 0;
}


