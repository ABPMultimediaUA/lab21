#include <iostream>
#include "Door.h"

using namespace std;

Door::Door( float i,  float u, int f, bool a)
{
    x = i;
    z = u;
    facing = f;

    // Los valores de la variable op deben ser modificados
    if(facing == 0)
    {
        op = x + 100;
        cl = x;
    }

    else if(facing == 1)
    {
        op=z+100;
        cl = z;
    }

    else if(facing == 2)
    {
        op=x-100;
        cl = x;
    }

    else if(facing == 3)
    {
        op=z+100;
        cl = z;
    }

    active = a;
    isOpening = false;
    isOpened = false;
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

void Door::openDoor()
{
    // Utilizar el get position de drawable
    // Desplazar la puerta hacia un lado
    switch (facing)
    {
        case 0:
            if(x<op)
                x+=0.05;
            setPosition(dwe::vec3f(0,0,x));
            isOpened = (x>=op);
            break;

        case 1:
            if(z<op)
                z+=0.05;
            isOpened = (z>=op);
            break;

        case 2:
            if(x>op)
                x-=0.05;
            isOpened =(x<=op);
            break;

        case 3:
            if(z>op)
                z-=0.05;
            isOpened =(z<=op);
            break;
    }

    if (isOpened)
        isOpening = false;
}

void Door::closeDoor()
{

    switch (facing)
    {
        case 0:
            if(x>cl)
                x-=0.05;
            setPosition(dwe::vec3f(0,0,x));
            isOpened=(x>=cl);
            break;

        case 1:
            if(z>cl)
                z-=0.05;
            isOpened=(z>=cl);
            break;

        case 2:
            if(x<cl)
                x+=0.05;
            isOpened=(x<=cl);
            break;

        case 3:
            if(z<cl)
                z+=0.05;
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
