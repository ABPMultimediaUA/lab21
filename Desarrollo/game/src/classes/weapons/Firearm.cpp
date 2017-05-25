#include "Firearm.h"
#include "Player.h"

Firearm::Firearm()
{
}

Firearm::~Firearm()
{
    //dtor
}

/////////////
float Firearm::getCadence() { return m_cadence; }

/////////////
int Firearm::getBulletsPerShot() { return m_bulletsPerShot; }
void Firearm::setBulletsPerShot(int b) { m_bulletsPerShot = b; }

/////////////
int Firearm::getClipSize() { return m_clipSize; }
void Firearm::setClipSize(int c) { m_clipSize = c; }
