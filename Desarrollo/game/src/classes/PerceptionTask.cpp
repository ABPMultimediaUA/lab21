#include "PerceptionTask.h"

PerceptionTask::PerceptionTask(Perception* p, Humanoid* h, PathplanningTask* pa)
{
    //ctor
    per = p;
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
    if(0)
        return success;
    return failure;
}
