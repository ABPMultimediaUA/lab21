#include "PerceptionTask.h"
#include "WorldInstance.h"

PerceptionTask::PerceptionTask(Perception* p, Humanoid* h, /*dwe::Node* n, */PathplanningTask* pa)
{
    //ctor
    per = p;
    play = World->getMainPlayer();
    hum = h;
    //no = n;
    path = pa;
    brunning = false;
}

PerceptionTask::~PerceptionTask()
{
    //dtor
}

States PerceptionTask::run()
{
    if(per->senses(play, hum, /*no,*/ path))
        return success;
    return failure;
}
