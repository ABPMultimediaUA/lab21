#include "Character.h"

Character::Character()
{
    //ctor
}

Character::~Character()
{
    //dtor
}

///////////////
int Character::getStrength(){ return m_strength; }
void Character::setStrength(int s) { m_strength = s; }

///////////////
int Character::getHealth() { return m_health; }
void Character::setHealth(int h) { m_health = h; }
