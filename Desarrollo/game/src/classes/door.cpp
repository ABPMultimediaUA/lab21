#include "door.h"

door::door(int i, int u, int f, bool a)
{
    AppReceiver* aappReceiver = new AppReceiver();
	GEInstance->init(aappReceiver);
    _door=GEInstance->createNode("media/puerta");
    _door->setPosition(dwe::vec3f(i,0,u));
    x=i;
    z=u;
    facing=f;
    // Los valores de la variable op deben ser modificados
    if(facing==0)
        op=x+100;
    else if(facing==1)
        op=z+100;
    else if(facing==2)
        op=x-100;
    else if(facing==3)
        op=z+100;
    active=a;
    isOpening=false;
    isOpened=false;
}

door::~door()
{
    //dtor
}

void door::setActive(){active=true;}

void door::openDoor()
{
    // Utilizar el get position de drawable
    // Desplazar la puerta hacia un lado
    switch (facing)
    {
        case 0:
            if(x<op)
                x++;
            isOpened=(x>=op);
            break;

        case 1:
            if(z<op)
                z++;
            isOpened=(z>=op);
            break;

        case 2:
            if(x>op)
                x--;
            isOpened=(x<=op);
            break;

        case 3:
            if(z>op)
                z--;
            isOpened=(z<=op);
            break;
    }
}

void door::setIsOpening()
{
    if(active)
        isOpening=true;
}

bool door::getIsOpening(){return isOpening;}

void door::update()
{
    if(active)
    {
        if(isOpening && !isOpened){
            openDoor();
        }else if(isOpened)
            delete this;
    }
}

void door::render()
{
    // dibujar nodo
}
