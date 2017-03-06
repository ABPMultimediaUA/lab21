#include "Consumable.h"
#include "Player.h"
#include "NetGame.h"

Consumable::Consumable()
{
    //ctor
    m_isTaken = false;
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
        if (this->getNode() != 0)
        {
            if(mainPlayer->getNode()->intersects(this->getNode()->getNode()))
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
    if (this->getNode() != 0)
    {
        this->removeNode();
        m_isTaken = true;
    }
}


/////////////////
void Consumable::setNetID(unsigned int netID) { m_netID = netID; }
