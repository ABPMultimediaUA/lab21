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
int Weapon::getAmmo() { return m_ammo; }
void Weapon::setAmmo(int ammo) { m_ammo = ammo; }
void Weapon::addAmmo(int ammo) { m_ammo += ammo; }

////////////
int Weapon::getDamage() { return m_damage; }
void Weapon::setDamage(int damage) { m_damage = damage; }

/////////////////
bool Weapon::getIsTaken() { return m_isTaken; }

/////////////////
void Weapon::take()
{
    if (this->hasNode())
    {
        this->removeNode();
        m_isTaken = true;
    }
}

/////////////////
void Weapon::setNetID(unsigned int netID) { m_netID = netID; }


