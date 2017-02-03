#include "Firearm.h"

Firearm::Firearm()
{
    //ctor
}

Firearm::~Firearm()
{
    //dtor
}

/////////////
int Firearm::getCadence() { return m_cadence; }
void Firearm::setCadence(int c) { m_cadence = c; }

/////////////
int Firearm::getBulletsPerShot() { return m_bulletsPerShot; }
void Firearm::setBulletsPerShot(int b) { m_bulletsPerShot = b; }

/////////////
int Firearm::getClipSize() { return m_clipSize; }
void Firearm::setClipSize(int c) { m_clipSize = c; }
