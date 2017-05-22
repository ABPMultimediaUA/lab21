#ifndef APPRECEIVER_H
#define APPRECEIVER_H

#include <GraphicsEngine.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


enum EKEY_CODE
{
    // Teclas asignadas a acciones
    KEY_EXIT                = sf::Keyboard::Escape,
    KEY_INIT_GAME           = sf::Keyboard::Return,
    KEY_DASH                = sf::Keyboard::Space,
    KEY_OPEN_DOOR           = sf::Keyboard::E,
    KEY_WEAPON_1            = sf::Keyboard::Num1,
    KEY_WEAPON_2            = sf::Keyboard::Num2,
    KEY_WEAPON_3            = sf::Keyboard::Num3,
    KEY_CONSUME_MEDKIT      = sf::Keyboard::Q,
    KEY_GIVE_AMMO           = sf::Keyboard::Num5,
    KEY_DUCK                = sf::Keyboard::Num8,
    KEY_LEFT                = sf::Keyboard::A,
    KEY_DOWN                = sf::Keyboard::S,
    KEY_RIGHT               = sf::Keyboard::D,
    KEY_UP                  = sf::Keyboard::W,
    KEY_CONSUME_SPEED       = sf::Keyboard::F,
    KEY_RELOADWEAPON        = sf::Keyboard::R,
    KEY_GRENADE             = sf::Keyboard::G,
    KEY_PAUSE               = sf::Keyboard::P,
    KEY_WALK                = sf::Keyboard::LShift,
    KEY_ATTACK              = sf::Keyboard::V,
    KEY_DO_DEAD             = sf::Keyboard::F9,
    KEY_BEGIN_DEBUG_PHYSICS = sf::Keyboard::F11,
    KEY_STOP_DEBUG_PHYSICS  = sf::Keyboard::F12,

    // Teclas generales. Si son para acciones, crear
    // nuevas teclas como las de arriba
    KEY_KEY_ESCAPE  = sf::Keyboard::Escape,
    KEY_KEY_RETURN  = sf::Keyboard::Return,
    KEY_KEY_SPACE   = sf::Keyboard::Space,
    KEY_KEY_0       = sf::Keyboard::Num0,
    KEY_KEY_1       = sf::Keyboard::Num1,
    KEY_KEY_2       = sf::Keyboard::Num2,
    KEY_KEY_3       = sf::Keyboard::Num3,
    KEY_KEY_4       = sf::Keyboard::Num4,
    KEY_KEY_5       = sf::Keyboard::Num5,
    KEY_KEY_6       = sf::Keyboard::Num6,
    KEY_KEY_7       = sf::Keyboard::Num7,
    KEY_KEY_8       = sf::Keyboard::Num8,
    KEY_KEY_9       = sf::Keyboard::Num9,
    KEY_KEY_A       = sf::Keyboard::A,
    KEY_KEY_B       = sf::Keyboard::B,
    KEY_KEY_C       = sf::Keyboard::C,
    KEY_KEY_D       = sf::Keyboard::D,
    KEY_KEY_E       = sf::Keyboard::E,
    KEY_KEY_G       = sf::Keyboard::G,
    KEY_KEY_M       = sf::Keyboard::M,
    KEY_KEY_N       = sf::Keyboard::N,
    KEY_KEY_P       = sf::Keyboard::P,
    KEY_KEY_S       = sf::Keyboard::S,
    KEY_KEY_W       = sf::Keyboard::W,
    KEY_KEY_X       = sf::Keyboard::X,
    KEY_LSHIFT      = sf::Keyboard::LShift,
    KEY_F9          = sf::Keyboard::F9,
    KEY_F10         = sf::Keyboard::F10,
};


class AppReceiver
{
private:
    bool KeyDown[sf::Keyboard::KeyCount];
    int cursorX;
    int cursorY;
    bool leftButton;

public:
    AppReceiver()
    {
        clearEvents();
    }

    virtual bool OnEvent(const sf::Event &event)
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
                KeyDown[event.key.code] = (event.type == sf::Event::KeyPressed);
                break;
            case sf::Event::MouseMoved:
                cursorX = event.mouseMove.x;
                cursorY = event.mouseMove.y;
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                switch (event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        leftButton = (event.type == sf::Event::MouseButtonPressed);
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

    virtual void clearEvents() {
        for(int i=0; i<sf::Keyboard::KeyCount; i++)
            KeyDown[i] = false;
        leftButton = false;
    }

    virtual float getCursorX(){return(cursorX);}
    virtual float getCursorY(){return(cursorY);}
    virtual bool isLeftButtonPressed(){return leftButton;}
    virtual bool isLeftButtonReleased(){return !leftButton;}
};

#endif // APPRECEIVER_H
