#include "Consumable.h"
#include "WorldInstance.h"
#include "NetGame.h"
#include "TriggerConsumable.h"
#include "Scene.h"

Consumable::Consumable() :
    m_isTaken(false)
{
    m_trigger = new TriggerConsumable(this);
    Scene::Instance()->getTriggerSystem().Add(m_trigger);
}

Consumable::~Consumable()
{
    delete m_trigger;
}

/////////////////
bool Consumable::getIsTaken() { return m_isTaken; }

/////////////////
void Consumable::Take()
{
    if (hasNode())
    {
        NetInstance->sendBroadcast(ID_CONSUMABLE_TAKEN, m_netID);  // enviamos a los demas que lo hemos cogido
        removeNode();

        m_isTaken = true;

        onTake(World->getMainPlayer());
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
}

/////////////////
void Consumable::setPosition(dwe::vec3f p)
{
    Drawable::setPosition(p);
    m_trigger->SetSensor();
}
