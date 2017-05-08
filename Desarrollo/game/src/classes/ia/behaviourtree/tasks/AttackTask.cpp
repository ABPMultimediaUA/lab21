#include "AttackTask.h"
#include "Enemy.h"
#include "WorldInstance.h"

AttackTask::AttackTask(Enemy* owner)
{
    m_owner = owner;
    brunning = false;
}

AttackTask::~AttackTask()
{
    //dtor
}

States AttackTask::run()
{
    if(m_owner->Attack()){
        brunning = true;
        return running;
    }
    brunning = false;
    return success;
}
