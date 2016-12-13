#include "CheckIfDoorIsOpenTask.h"

CheckIfDoorIsOpenTask::CheckIfDoorIsOpenTask(Door* d)
{
    //ctor
    door = d;
    brunning = false;
}

CheckIfDoorIsOpenTask::~CheckIfDoorIsOpenTask()
{
    //dtor
}

States CheckIfDoorIsOpenTask::run()
{
    if (door->getIfOpened())
    {
        //cout << "The npc sees that the door is open." << endl;  // will return true
        return success;
    }

    //cout << "The npc sees that the door is closed." << endl;  // will return false

    return failure;

}
