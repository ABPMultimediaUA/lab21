#include "WalkThroughDoorTask.h"

WalkThroughDoorTask::WalkThroughDoorTask(Humanoid* n, Door* d)
{
    //ctor
    brunning = false;
    door = d;
    npc = n;
}

WalkThroughDoorTask::~WalkThroughDoorTask()
{
    //dtor
}

States WalkThroughDoorTask::run()
{

    cout << "The npc is walking through the door." << endl;

    return success;
}
