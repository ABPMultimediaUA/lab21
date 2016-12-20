#include "ApproachDoorTask.h"


ApproachDoorTask::ApproachDoorTask(Humanoid* n, Door* d)
{
    npc = n;
    door = d;
    brunning = false;
}

ApproachDoorTask::~ApproachDoorTask()
{
    //dtor

}

States ApproachDoorTask::run()
{
    dwe::vec3f posNpc = npc->getPosition();

    dwe::vec3f posDoor = door->getPosition();

    if(posNpc.z < posDoor.z - 50)
    {

        npc->setPosition(dwe::vec3f(posNpc.x, posNpc.y, posNpc.z + 0.1));
        //cout << "The npc is one step closer." << endl;

        //mapa->setMap(npc->getPosition());

        brunning = true;
        return running;
    }

    //cout << "The npc is at the door." << endl;

    brunning = false;
    return success;
}
