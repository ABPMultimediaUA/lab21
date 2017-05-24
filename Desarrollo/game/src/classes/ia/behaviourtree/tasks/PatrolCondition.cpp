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
    dwe::vec2f ownerPos(m_owner->getPosEntity().x, m_owner->getPosEntity().z);
    dwe::vec2f ownerPat(m_owner->GetPatrolPosition());
    if( (abs(ownerPos.x - ownerPat.x) < m_owner->getSpeed() && abs(ownerPos.y - ownerPat.y) < m_owner->getSpeed()) )
    {
        m_owner->ChangePatrolPosition();
    }
    m_owner->SetTargetPosition(ownerPat);
    return success;
}
