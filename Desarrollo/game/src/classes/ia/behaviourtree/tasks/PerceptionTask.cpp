#include "PerceptionTask.h"
#include "Enemy.h"

PerceptionTask::PerceptionTask(Enemy* owner)
{
    m_owner = owner;
    brunning = false;
}

PerceptionTask::~PerceptionTask()
{
    //dtor
}

States PerceptionTask::run()
{
    m_owner->Sense();
    return success;
}
