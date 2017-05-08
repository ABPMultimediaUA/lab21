#include "PatrolCondition.h"
#include "Enemy.h"

PatrolCondition::PatrolCondition(Enemy* owner)
{
    m_owner = owner;
    brunning = false;
}

PatrolCondition::~PatrolCondition()
{
    //dtor
}

States PatrolCondition::run()
{
    return success;
}
