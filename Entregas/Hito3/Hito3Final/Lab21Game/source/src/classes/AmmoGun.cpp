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
void AmmoGun::onTake(Player* mainplayer)
{
    //mainplayer->addAmmo(0,10);
    mainplayer->getPlayerGun()->addAmmo(10);
}

/////////////////////
FirearmKind AmmoGun::getKind() { return m_kind; }
void AmmoGun::setKind(FirearmKind k) { m_kind = k; }
