#include "AmmoRifle.h"

AmmoRifle::AmmoRifle()
{
    //ctor
}

AmmoRifle::~AmmoRifle()
{
    //dtor
}

//////////////////
void AmmoRifle::onTake()
{
    // TODO
}

/////////////////////////
FirearmKind AmmoRifle::getKind() { return m_kind; }
void AmmoRifle::setKind(FirearmKind k) { m_kind = k; }
