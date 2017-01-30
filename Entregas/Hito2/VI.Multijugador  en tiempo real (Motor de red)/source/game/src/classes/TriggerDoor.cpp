#include "TriggerDoor.h"

TriggerDoor::TriggerDoor()
{
    //ctor
}

TriggerDoor::~TriggerDoor()
{
    //dtor
}

void TriggerDoor::triggered(Entity *e)
{
    if(((Door*)e)->getIfOpened())
    {
        ((Door*)e)->setIsClosing();
    }
    else
    {
        ((Door*)e)->setIsOpening();
    }
}

void TriggerDoor::render()
{

}

void TriggerDoor::update()
{

}
