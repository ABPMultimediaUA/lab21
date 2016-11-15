#include "PlayerMate.h"

PlayerMate::PlayerMate()
{
    //ctor
}

PlayerMate::~PlayerMate()
{
    //dtor
}

fde::vec3f PlayerMate::getShift() { return m_shift; }
void PlayerMate::setShift(fde::vec3f s) { m_shift = s;}
unsigned short int PlayerMate::getHealth() { return m_health; }
void PlayerMate::setHealth(unsigned short int h) { m_health = h;}
bool PlayerMate::getHasRifle() { return m_hasRifle; }
void PlayerMate::setHasRifle(unsigned short int h) { m_hasRifle = h;}
bool PlayerMate::getHasShotgun() { return m_hasShotgun; }
void PlayerMate::setHasShotgun(unsigned short int h) { m_hasShotgun = h;}
unsigned short int PlayerMate::getNumGrenades() { return m_numGrenades; }
void PlayerMate::setNumGrenades(unsigned short int n) { m_numGrenades = n;}
unsigned short int PlayerMate::getNumMedkits() { return m_numMedkits; }
void PlayerMate::setNumMedkits(unsigned short int n) { m_numMedkits = n;}
