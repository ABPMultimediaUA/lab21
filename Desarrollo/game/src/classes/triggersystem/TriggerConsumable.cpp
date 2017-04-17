#include "TriggerConsumable.h"
#include "Consumable.h"

TriggerConsumable::TriggerConsumable(Consumable* owner)
{
    m_owner = owner;
    m_touchingMainPlayer = false;
}

TriggerConsumable::~TriggerConsumable()
{
    //dtor
}

void TriggerConsumable::SetSensor()
{
    dwe::vec3f s = m_owner->getNode()->getBoundingBox();
    createStaticBody(m_owner->getPosition(), s.x, s.z, m_owner->getRotation().y);
}

void TriggerConsumable::Update()
{
    if (m_touchingMainPlayer){
        m_owner->Take();
        ToBeRemoved = true;
    }
}

void TriggerConsumable::onBeginContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = true;
    }
}

void TriggerConsumable::onEndContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = false;
    }
}
