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

}

/////////////////
bool Consumable::getIsTaken() { return m_isTaken; }

bool Consumable::couldTake(Player* mainPlayer)
{
    // Si no se implementa en hijos, siempre verdadero
    return true;
}

/////////////////
void Consumable::Take()
{
    if (hasNode())
    {
        Player* player = World->getMainPlayer();
        if (couldTake(player))
        {
            NetInstance->sendBroadcast(ID_CONSUMABLE_TAKEN, m_netID);  // enviamos a los demas que lo hemos cogido
            removeNode();

            m_isTaken = true;

            onTake(World->getMainPlayer());
        }
    }
}

/////////////////
void Consumable::take()
{
    if (hasNode())
    {
        removeNode();
        m_isTaken = true;
        m_trigger->SetToBeRemoved();
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
