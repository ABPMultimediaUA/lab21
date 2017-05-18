#include "Weapon.h"
#include "Player.h"
#include "AudioEngine.h"

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

///////////////////
int  Weapon::getAmmoClip(){ return m_ammoClip; }
void Weapon::setAmmoClip(int ammo) { m_ammoClip = ammo; }
void Weapon::addAmmoClip(int ammo) { m_ammoClip += ammo ; }

////////////
int Weapon::getAmmoBag() { return m_bagAmmo; }
void Weapon::setAmmoBag(int ammo) { m_bagAmmo = ammo; }
void Weapon::addAmmoBag(int ammo) { m_bagAmmo += ammo; }

////////////
bool Weapon::reload()
{
    if (m_ammo < m_ammoClip && m_bagAmmo > 0)
    {
        AEInstance->Play2D("media/Sounds/PistolaRecarga.wav");
        int reload = m_ammoClip - m_ammo;
        if(m_bagAmmo>=reload)
        {
            m_ammo += reload;
            m_bagAmmo -= reload;
        }
        else
        {
            m_ammo += m_bagAmmo;
            m_bagAmmo = 0;
        }
        return true;
    }
    return false;
}
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


