#include "ElapsedTimeCondition.h"
#include "Enemy.h"
#include "WorldInstance.h"

ElapsedTimeCondition::ElapsedTimeCondition(Enemy* owner, float time)
{
    m_owner = owner;
    waitTime = time;
    lastTime = World->getTimeElapsed() - waitTime;
    brunning = false;
}

ElapsedTimeCondition::~ElapsedTimeCondition()
{
    //dtor
}

States ElapsedTimeCondition::run()
{
    if(World->getTimeElapsed() - lastTime >= waitTime){
        lastTime = World->getTimeElapsed();
        return success;
    }
    return failure;
}
