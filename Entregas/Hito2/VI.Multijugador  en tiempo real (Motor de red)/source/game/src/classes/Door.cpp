#include "Door.h"
#include "NetGame.h"

Door::Door(int f, bool a)
{
    x = 0;
    y = 0;
    z = 0;
    facing = f;
    speed = 0.6;  // RMM no se puede poner a 0.5, sino la puerta no vuelve a abrirse �?
    active = a;
    isOpened = false;
    op=0;
    cl=0;
    isOpening = false;
    isClosing = false;
}

Door::~Door()
{
    //dtor
}

void Door::setActive(){ active=true; }

bool Door::getActive(){ return active; }

bool Door::getIfOpened()
{
    return isOpened;
}


void Door::setPositionClosed(dwe::vec3f p)
{

     if (facing == 0 || facing == 2)
     {
         cl = p.x;
     }
     else
     {
         cl = p.z;
     }
}

void Door::setPositionOpened(dwe::vec3f p)
{
    if(facing==0)
        op=p.x+50.5;
    else if(facing==1)
        op=p.z+50.5;
    else if(facing==2)
        op=p.x-50.5;
    else if(facing==3)
        op=p.z-50.5;
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
    {
        isOpening = true;
        NetInstance->sendBroadcast(ID_DOOR_OPEN, m_netID);
    }
}

bool Door::getIsOpening()
{
    return isOpening;
}

void Door::setIsClosing()
{
    if(active && isOpened)
    {
        isClosing = true;
        NetInstance->sendBroadcast(ID_DOOR_CLOSE, m_netID);
    }
}

bool Door::getIsClosing()
{
    return isClosing;
}


void Door::update()
{
    //cout<<"Updateando"<<endl;
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

void Door::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f s = n->getBoundingBox();
    createStaticBody(getPosition(), s.x, s.z);
}

void Door::setPosition(dwe::vec3f p)
{
    int rotation=0;
    if(facing==1 ||facing ==3)
        rotation=90;
    setPosEntity(p, rotation);
    Drawable::setPosition(p);
}
