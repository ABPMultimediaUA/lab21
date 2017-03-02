#include "Weapon.h"
#include "Player.h"

Weapon::Weapon()
{
    //ctor
    m_isTaken = false;
}

Weapon::~Weapon()
{
    //dtor
}

////////////
int Weapon::getDamage() { return m_damage; }
void Weapon::setDamage(int damage) { m_damage = damage; }

/////////////////
bool Weapon::getIsTaken() { return m_isTaken; }
/////////////////
void Weapon::check(Player* mainPlayer){
    if(!m_isTaken){
        if (this->getNode() != 0){
            if(mainPlayer->getNode()->intersects(this->getNode()->getNode())){
                NetInstance->sendBroadcast(ID_WEAPON_TAKEN, m_netID);  // enviamos a los demas que lo hemos cogido
                //this->removeNode();
                //AQUI NO SE TIENE QUE HACER UN REMOVENODE...
                //SOLO SE TIENE QUE DEJAR DE DIBUJAR Y METER EN "LA MOCHILA" DEL PERSONAJE

                m_isTaken = true;
                onTake(mainPlayer);
            }
        }
    }
}

/////////////////
void Weapon::take()
{
    if (this->getNode() != 0)
    {
        this->removeNode();
        m_isTaken = true;
    }
}


/////////////////
void Weapon::setNetID(unsigned int netID) { m_netID = netID; }


