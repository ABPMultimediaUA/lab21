#include "PatrolTask.h"

PatrolTask::PatrolTask(Humanoid* h/*, dwe::Node* n*/)
{
    //ctor
    hum = h;
    //no = n;
    pos1 = 100;
    pos2 = -100;
    dir = 0;
    brunning = false;
}

PatrolTask::~PatrolTask()
{
    //dtor
}

States PatrolTask::run()
{
    //dwe::vec3f posNpc = hum->getPosition();ww
    dwe::vec3f posEnt = hum->getPosEntity();

    if(!dir)
    {
        //hum->setPosition(dwe::vec3f(posNpc.x, posNpc.y, posNpc.z - 0.1));
        hum->setPosEntity(dwe::vec3f(posEnt.x, posEnt.y, posEnt.z - 0.1), 90);
        if(posEnt.z<=pos2){
            dir = 1;
            //hum->setRotation(dwe::vec3f(0, 270.f, 0));
            //no->setRotation(hum->getRotation());
        }
    }
    else
    {
        //hum->setPosition(dwe::vec3f(posNpc.x, posNpc.y, posNpc.z + 0.1));
        hum->setPosEntity(dwe::vec3f(posEnt.x, posEnt.y, posEnt.z + 0.1), 90);
        if(posEnt.z>=pos1){
            dir = 0;
            //hum->setRotation(dwe::vec3f(0, 90.f, 0));
            //no->setRotation(hum->getRotation());
        }
    }

    return success;
}
