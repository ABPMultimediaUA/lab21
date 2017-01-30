#include "AmmoGun.h"

AmmoGun::AmmoGun()
{
    //ctor
}

AmmoGun::~AmmoGun()
{
    //dtor
}

//////////////
void AmmoGun::onTake()
{
    // TODO
}

/////////////////////
FirearmKind AmmoGun::getKind() { return m_kind; }
void AmmoGun::setKind(FirearmKind k) { m_kind = k; }
