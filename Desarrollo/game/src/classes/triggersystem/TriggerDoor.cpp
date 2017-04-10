#include "TriggerDoor.h"
#include "WorldInstance.h"

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

void TriggerDoor::update(Entity *e)
{
    if (m_touchingMainPlayer && GEInstance->receiver.isKeyDown(KEY_OPEN_DOOR))
        triggered(e);
}
