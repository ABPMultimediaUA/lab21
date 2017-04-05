#include "OpenDoorTask.h"

OpenDoorTask::OpenDoorTask(Door* d)
{
    //ctor
    door = d;
    brunning = false;
}

OpenDoorTask::~OpenDoorTask()
{
    //dtor
}

States OpenDoorTask::run()
{

    if (door->getIfOpened())
    {
       // Already opened
        return failure;
    }

    door->setIsOpening();

    //cout << "The npc opens the door." << endl;

    return success;
}
