#include "TriggerDamage.h"
#include "Enemy.h"
#include "WorldInstance.h"

TriggerDamage::TriggerDamage(dwe::vec3f pos, float radius, int damage, float angle)
{
    setClassID(EntityPhysics::triggerDamage_id);
    createSemiCircleBody(pos, radius, angle);
    lastTime = World->getTimeElapsed();
    m_damage = damage;
}

TriggerDamage::~TriggerDamage()
{
    //dtor
}

void TriggerDamage::Update()
{
    if(World->getTimeElapsed() - lastTime >= 10.0f/60.0f)
        SetToBeRemoved();
}

int TriggerDamage::getDamage()
{
    return m_damage;
}
