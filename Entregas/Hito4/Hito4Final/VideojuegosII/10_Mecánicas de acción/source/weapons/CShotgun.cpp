#include "CShotgun.h"

CShotgun::CShotgun()
{
    //ctor
}

CShotgun::~CShotgun()
{
    //dtor
}

///////////////
bool CShotgun::couldTake(Player* mainplayer)
{
    return (!mainplayer->getPlayerShotgun());
}

///////////////
void CShotgun::onTake(Player* mainplayer)
{
    mainplayer->addWeapon(eShotgun);
}

//////////////////////
FirearmKind CShotgun::getKind() { return m_kind; }
void CShotgun::setKind(FirearmKind k) { m_kind = k; }
