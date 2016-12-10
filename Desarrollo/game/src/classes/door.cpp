#include <iostream>
#include "Door.h"

using namespace std;

Door::Door(int i, int u, int f, bool a)
{
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

Door::~Door()
{
    //dtor
}

void Door::setActive(){active=true;}

void Door::openDoor()
{
    // Utilizar el get position de drawable
    // Desplazar la puerta hacia un lado
    switch (facing)
    {
        case 0:
            if(x<op)
                x++;
            setPosition(dwe::vec3f(0,0,x));
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

void Door::setIsOpening()
{
    if(active)
        isOpening=true;
}

bool Door::getIsOpening(){return isOpening;}

void Door::update()
{
    cout<<"Hola1"<<endl;
    if(active)
    {
        cout<<"Hola2"<<endl;
        if(isOpening && !isOpened){
            cout<<"Hola3"<<endl;
            openDoor();
        }else if(isOpened){
            cout<<"Hola4"<<endl;
            //delete this;
        }
    }
}

void Door::render()
{
    // dibujar nodo
}
