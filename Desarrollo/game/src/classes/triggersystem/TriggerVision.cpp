#include "TriggerVision.h"
#include "Enemy.h"

TriggerVision::TriggerVision(Enemy* owner)
{
    m_owner = owner;
    setClassID(EntityPhysics::triggerVision_id);
    createSemiCircleBody(m_owner->getPosition(), 7.0f, m_owner->getRotation().y, 120);
    m_touchingMainPlayer = false;
    m_playerEntity = 0;
}

TriggerVision::~TriggerVision()
{
    //dtor
}

void TriggerVision::Update()
{
    setPosEntity(m_owner->getPosEntity(), m_owner->getRotation().y+m_arc/2);
    if (m_touchingMainPlayer && !ToBeRemoved){
        m_owner->SeePlayer(m_playerEntity->getPosEntity());
    }
}

void TriggerVision::onBeginContact(EntityPhysics* otherObject)
{
    if (otherObject && (otherObject->getClassID() == EntityPhysics::player_id
                    || otherObject->getClassID() == EntityPhysics::playermate_id))
    {
        m_touchingMainPlayer = true;
        m_playerEntity = otherObject;
    }
}

void TriggerVision::onEndContact(EntityPhysics* otherObject)
{
    if (otherObject && (otherObject->getClassID() == EntityPhysics::player_id
                    || otherObject->getClassID() == EntityPhysics::playermate_id))
    {
        m_touchingMainPlayer = false;
    }
}
