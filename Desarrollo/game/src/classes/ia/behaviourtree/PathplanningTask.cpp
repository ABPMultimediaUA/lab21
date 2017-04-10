#include "PathplanningTask.h"
#include "Enemy.h"
#include "WorldInstance.h"

PathplanningTask::PathplanningTask(Enemy* owner)
{
    m_owner = owner;
    brunning = false;
    lastTime = World->getTimeElapsed() - 1;
}

PathplanningTask::~PathplanningTask()
{
    //dtor
}

States PathplanningTask::run()
{
    if(World->getTimeElapsed() - lastTime >= 1){
        m_owner->PlanPath();
        lastTime = World->getTimeElapsed();
    }
    return success;
}
