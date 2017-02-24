#ifndef APPRECEIVER_H
#define APPRECEIVER_H

#include <GraphicsEngine.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


enum EKEY_CODE
{
    KEY_ESCAPE      = sf::Keyboard::Escape,
    KEY_RETURN      = sf::Keyboard::Return,
    KEY_SPACE       = sf::Keyboard::Space,
    KEY_KEY_A       = sf::Keyboard::A,
    KEY_KEY_C       = sf::Keyboard::C,
    KEY_KEY_D       = sf::Keyboard::D,
    KEY_KEY_M       = sf::Keyboard::M,
    KEY_KEY_S       = sf::Keyboard::S,
    KEY_KEY_W       = sf::Keyboard::W,
    KEY_KEY_X       = sf::Keyboard::X,
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
        for(int i=0; i<sf::Keyboard::KeyCount; i++)
        {
            KeyDown[i] = false;
        }
        leftButton = false;
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

    virtual float getCursorX(){return(cursorX);}
    virtual float getCursorY(){return(cursorY);}
    virtual bool isLeftButtonPressed(){return leftButton;}
};

#endif // APPRECEIVER_H
