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
    if(m_owner->Sense() || m_owner->RouteEnd())
        return success;
    /*dwe::vec2f pos(m_owner->getPosition().x, m_owner->getPosition().z);
    m_owner->SetTargetPosition(dwe::vec2f(pos.x+rand()%101-50, pos.y+rand()%101-50));*/
    return failure;
}
