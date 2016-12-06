#ifndef APPRECEIVER_H
#define APPRECEIVER_H

#include <irrlicht.h>

using namespace irr;

class AppReceiver : public IEventReceiver
{
    private:
        bool KeyDown[KEY_KEY_CODES_COUNT];

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
};

#endif // APPRECEIVER_H
