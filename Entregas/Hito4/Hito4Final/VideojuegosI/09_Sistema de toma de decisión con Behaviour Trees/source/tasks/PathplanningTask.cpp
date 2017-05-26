#include "PathplanningTask.h"
#include "Enemy.h"

PathplanningTask::PathplanningTask(Enemy* owner)
{
    m_owner = owner;
    brunning = false;
}

PathplanningTask::~PathplanningTask()
{
    //dtor
}

States PathplanningTask::run()
{
    if(m_owner->RouteEnd())
        m_owner->PlanPath();
    return success;
}
