#include <iostream>
#include "Door.h"

using namespace std;

Door::Door(int f, bool a)
{
    x = 0;
    y = 0;
    z = 0;
    facing = f;
    speed = 0.1;
    active = a;
    isOpened = false;

    if (!isOpened) // Puerta inicialmente cerrada
    {
        // Los valores de la variable op deben ser modificados
        if(facing == 0)
        {
            op = x + 7;
            cl = x;
        }

        else if(facing == 1)
        {
            op=z+7;
            cl = z;
        }

        else if(facing == 2)
        {
            op = x - 7;
            cl = x;
        }

        else if(facing == 3)
        {
            op= z - 7;
            cl = z;
        }
    }
    else // Puerta inicialmente abierta
    {
        // Los valores de la variable op deben ser modificados
        if(facing == 0)
        {
            op = x ;
            cl = x - 7;
        }

        else if(facing == 1)
        {
            op = z;
            cl = z - 7;
        }

        else if(facing == 2)
        {
            op = x;
            cl = x + 7;
        }

        else if(facing == 3)
        {
            op = z;
            cl = z + 7;
        }
    }



    isOpening = false;
    isClosing = false;
}

Door::~Door()
{
    //dtor
}

void Door::setActive(){active=true;}

bool Door::getIfOpened()
{
    return isOpened;
}


void Door::setPositionClosed(dwe::vec3f p)
{

     if (facing == 0 || facing == 2)
        cl = p.x;
     else
        cl = p.z;
}

void Door::openDoor()
{
    // Utilizar el get position de drawable
    // Desplazar la puerta hacia un lado

    x = getPosition().x;
    y = getPosition().y;
    z = getPosition().z;



    switch (facing)
    {
        case 0:

            if(x<op)
                x += speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened = (x>=op);

            break;

        case 1:

            if(z<op)
                z+= speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened = (z>=op);

            break;

        case 2:

            if(x>op)
                x-= speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened =(x<=op);

            break;

        case 3:

            if(z>op)
                z-=speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened =(z<=op);

            break;
    }

    if (isOpened)
        isOpening = false;
}

void Door::closeDoor()
{

    x = getPosition().x;
    y = getPosition().y;
    z = getPosition().z;


    switch (facing)
    {
        case 0:

            if(x>cl)
                x-=speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened=(x>=cl);

            break;

        case 1:

            if(z>cl)
                z-=speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened=(z>=cl);

            break;

        case 2:

            if(x<cl)
                x+=speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened=(x<=cl);

            break;

        case 3:

            if(z<cl)
                z+=speed;

            setPosition(dwe::vec3f(x,y,z));
            isOpened=(z<=cl);

            break;
    }

    if (!isOpened)
        isClosing = false;
}

void Door::setIsOpening()
{
    if(active && !isOpened)
        isOpening = true;
}

bool Door::getIsOpening()
{
    return isOpening;
}

void Door::setIsClosing()
{
    if(active && isOpened)
        isClosing = true;
}

bool Door::getIsClosing()
{
    return isClosing;
}


void Door::update()
{
    if(active)
    {
        if(isOpening && !isOpened)
        {
            openDoor();
        }/*else if(isOpened){
            delete this;
        }*/
        else if (isClosing && isOpened)
        {
            closeDoor();
        }

    }
}

void Door::render()
{
    // dibujar nodo
}
