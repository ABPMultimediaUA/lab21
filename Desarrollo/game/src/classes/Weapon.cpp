#include "Weapon.h"

Weapon::Weapon()
{
    //ctor
}

Weapon::~Weapon()
{
    //dtor
}

/////////////
void Weapon::shoot()
{
    // TODO
}


////////////
int Weapon::getDamage() { return m_damage; }
int Weapon::getAmmo() { return m_ammo; }
void Weapon::setDamage(int damage) { m_damage = damage; }
