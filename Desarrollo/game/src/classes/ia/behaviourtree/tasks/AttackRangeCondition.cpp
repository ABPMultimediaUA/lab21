#include "AttackRangeCondition.h"
#include "Enemy.h"

AttackRangeCondition::AttackRangeCondition(Enemy* owner)
{
    m_owner = owner;
    brunning = false;
}

AttackRangeCondition::~AttackRangeCondition()
{
    //dtor
}

States AttackRangeCondition::run()
{
    if(m_owner->IsInAttackRange())
        return success;
    return failure;
}
