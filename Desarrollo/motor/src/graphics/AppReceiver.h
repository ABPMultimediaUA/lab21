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
        int cursorX;
        int cursorY;
        bool leftButton;

    public:
    AppReceiver()
    {
        for(int i=0; i<KEY_KEY_CODES_COUNT; i++)
        {
            KeyDown[i] = false;
        }
        leftButton = false;
        //return 0;
    }

    virtual bool OnEvent(const SEvent &event)
    {
        switch(event.EventType)
        {
            case irr::EET_KEY_INPUT_EVENT:
                KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
                break;
            case irr::EET_MOUSE_INPUT_EVENT:
                switch(event.MouseInput.Event)
                {
                    case EMIE_MOUSE_MOVED:
                        cursorX = event.MouseInput.X;
                        cursorY = event.MouseInput.Y;
                        break;
                    case EMIE_LMOUSE_PRESSED_DOWN:
                        leftButton = true;
                        break;
                    case EMIE_LMOUSE_LEFT_UP:
                        leftButton = false;
                        break;
                    default:
                        break;
                }
                break;
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
    virtual bool isLeftButtonPressed(){return leftButton;}
};

#endif // APPRECEIVER_H
