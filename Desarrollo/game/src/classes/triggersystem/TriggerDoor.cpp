#include "TriggerDoor.h"
#include "Door.h"

TriggerDoor::TriggerDoor(Door* owner)
{
    m_owner = owner;
    m_touchingMainPlayer = false;
}

TriggerDoor::~TriggerDoor()
{
    //dtor
}

void TriggerDoor::SetSensor()
{
    dwe::vec3f s = m_owner->getNode()->getBoundingBox();
    createStaticSensorBody(m_owner->getPosition(), s.x*2, s.z*2, m_owner->getRotation().y);
}

void TriggerDoor::Update()
{
    if (m_touchingMainPlayer && GEInstance->receiver.isKeyDown(KEY_OPEN_DOOR)){
        if(m_owner->getIfOpened())
            m_owner->setIsClosing();
        else
            m_owner->setIsOpening();
    }
    m_owner->update();
}

void TriggerDoor::onBeginContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = true;
    }
}

void TriggerDoor::onEndContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = false;
    }
}
