#include "MoveTask.h"
#include "Enemy.h"

MoveTask::MoveTask(Enemy* owner)
{
    m_owner = owner;
    brunning = false;
}

MoveTask::~MoveTask()
{
    //dtor
}

States MoveTask::run()
{
    m_owner->move();
    return success;
}
