#ifndef APPRECEIVER_H
#define APPRECEIVER_H

#include <irrlicht.h>
#include <GraphicsEngine.h>
#include <iostream>
using namespace std;

using namespace irr;

class AppReceiver : public IEventReceiver
{
    private:
        bool KeyDown[KEY_KEY_CODES_COUNT];
        float cursorX;
        float cursorY;

    public:
    AppReceiver()
    {
        for(int i=0; i<KEY_KEY_CODES_COUNT; i++)
        {
            KeyDown[i] = false;
        }
        //return 0;
    }

    virtual bool OnEvent(const SEvent &event)
    {
        switch(event.EventType)
        {
        case irr::EET_KEY_INPUT_EVENT:
        {
            KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        }
        case irr::EET_MOUSE_INPUT_EVENT:
        {
            if (event.MouseInput.Event == EMIE_MOUSE_MOVED )
            {
                cursorX = event.MouseInput.X;
                cursorY = event.MouseInput.Y;
            }
            //cout << "Mouse at 2D coordinates: " << cursor.X << "," << cursor.Y << endl;
        }
        default:
            break;
        }
        return false;
    }
    virtual bool isKeyDown(EKEY_CODE keyCode) const {
        return KeyDown[keyCode];
    }
    virtual bool isKeyUp(EKEY_CODE keyCode) const {
        return !KeyDown[keyCode];
    }

    virtual float getCursorX(){return(cursorX);}
    virtual float getCursorY(){return(cursorY);}
};

#endif // APPRECEIVER_H
