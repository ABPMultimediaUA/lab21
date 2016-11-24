#include "AmmoShotgun.h"

AmmoShotgun::AmmoShotgun()
{
    //ctor
}

AmmoShotgun::~AmmoShotgun()
{
    //dtor
}

//////////////////
void AmmoShotgun::onTake()
{
    // TODO
}

/////////////////////////
FirearmKind AmmoShotgun::getKind() { return m_kind; }
void AmmoShotgun::setKind(FirearmKind k) { m_kind = k; }
