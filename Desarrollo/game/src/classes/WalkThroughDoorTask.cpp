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

    dwe::vec3f posNpc = npc->getPosition();

    dwe::vec3f posDoor = door->getPosition();

    if (!door->getIfOpened())
    {
        brunning = true;
        return running;
    }

    else if (posNpc.x < posDoor.x + 40)
    {
        npc->setPosition(dwe::vec3f(posNpc.x + 0.1, posNpc.y, posNpc.z));

        brunning = true;
        return running;
    }


    return success;
}
