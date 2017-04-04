#include "Consumable.h"
#include "Player.h"
#include "NetGame.h"
#include "WorldInstance.h"

Consumable::Consumable() :
    m_touchingMainPlayer(false),
    m_isTaken(false)
{
    //ctor
}

Consumable::~Consumable()
{
    //dtor
}

/////////////////
bool Consumable::getIsTaken() { return m_isTaken; }

/////////////////
void Consumable::update(Player* mainPlayer)
{
    if(!m_isTaken)
    {
        if (this->hasNode())
        {
            if(m_touchingMainPlayer)
            {
                NetInstance->sendBroadcast(ID_CONSUMABLE_TAKEN, m_netID);  // enviamos a los demas que lo hemos cogido
                this->removeNode();

                m_isTaken = true;
                onTake(mainPlayer);
            }
        }
    }
}

/////////////////
void Consumable::take()
{
    if (this->hasNode())
    {
        this->removeNode();
        m_isTaken = true;
    }
}


/////////////////
void Consumable::setNetID(unsigned int netID) { m_netID = netID; }


/////////////////
void Consumable::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f s = n->getBoundingBox();
    createSensorBody(getPosition(), s.x, s.z, getRotation().y);
}

/////////////////
void Consumable::setPosition(dwe::vec3f p)
{
    setPosEntity(p, getRotation().y);
    Drawable::setPosition(p);
}

/////////////////
void Consumable::onBeginContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = true;
    }
}

/////////////////
void Consumable::onEndContact(EntityPhysics* otherObject)
{
    if (otherObject && otherObject->getClassID() == EntityPhysics::player_id)
    {
        m_touchingMainPlayer = false;
    }
}

