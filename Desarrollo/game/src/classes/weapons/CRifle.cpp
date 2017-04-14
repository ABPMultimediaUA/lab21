#include "CRifle.h"

CRifle::CRifle()
{
    //ctor
}

CRifle::~CRifle()
{
    //dtor
}

///////////////
void CRifle::onTake(Player* mainplayer)
{
    mainplayer->addWeapon(eRifle);
}

////////////////////
FirearmKind CRifle::getKind() { return m_kind; }
void CRifle::setKind(FirearmKind k) { m_kind = k; }
