#include "TriggerGenerator.h"
#include "Generator.h"
#include "WorldInstance.h"
#include "Player.h"

TriggerGenerator::TriggerGenerator(Generator* owner)
{
    m_owner = owner;
    m_touchingMainPlayer = false;
}

TriggerGenerator::~TriggerGenerator()
{
    //dtor
}

void TriggerGenerator::SetSensor()
{
    dwe::vec3f s = m_owner->getNode()->getBoundingBox();
    createStaticBody(m_owner->getPosition(), s.x*2, s.z*2, m_owner->getRotation().y);
}

void TriggerGenerator::Update()
{
    if(m_touchingMainPlayer && World->getMainPlayer()->getMKey(m_owner->getNum()) && GEInstance->receiver.isKeyDown(KEY_OPEN_DOOR))
    {
        if(!m_owner->getIsActive())
        {
            m_owner->activateGenerator();
            std::cout<<"GENERATOR "<<m_owner->getNum()<<" ACTIVATED"<<std::endl;
        }
    }
}

void TriggerGenerator::onBeginContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = true;
    }
}

void TriggerGenerator::onEndContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = false;
    }
}
