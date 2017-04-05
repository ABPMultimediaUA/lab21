#include "CloseDoorTask.h"

CloseDoorTask::CloseDoorTask(Door* d)
{
    //ctor
    door = d;
    brunning = false;

}

CloseDoorTask::~CloseDoorTask()
{
    //dtor
}

States CloseDoorTask::run()
{
    if (!door->getIfOpened())
        return failure;

    door->setIsClosing();

    //cout << "The npc closes the door." << endl;

    return success;

}
