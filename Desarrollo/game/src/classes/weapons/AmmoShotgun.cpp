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
void AmmoShotgun::onTake(Player* mainplayer)
{
    // TODO
    mainplayer->getPlayerShotgun()->addAmmoBag(8);
}

/////////////////////////
FirearmKind AmmoShotgun::getKind() { return m_kind; }
void AmmoShotgun::setKind(FirearmKind k) { m_kind = k; }
