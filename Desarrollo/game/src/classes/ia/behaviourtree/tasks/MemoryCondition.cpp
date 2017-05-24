#include "MemoryCondition.h"
#include "Enemy.h"

MemoryCondition::MemoryCondition(Enemy* owner)
{
    m_owner = owner;
    checked = false;
    brunning = false;
}

MemoryCondition::~MemoryCondition()
{
    //dtor
}

States MemoryCondition::run()
{
    if(m_owner->HasMemory()){
        dwe::vec2f ownerPos(m_owner->getPosEntity().x, m_owner->getPosEntity().z);
        dwe::vec2f ownerMem(m_owner->GetMemoryPosition());
        m_owner->SetTargetPosition(ownerMem);

        if( !(abs(ownerPos.x - ownerMem.x) < m_owner->getSpeed() && abs(ownerPos.y - ownerMem.y) < m_owner->getSpeed()) )
            return success;
        m_owner->SetMemory(false);
    }
    return failure;
}
