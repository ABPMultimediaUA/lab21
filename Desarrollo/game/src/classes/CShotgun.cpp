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
void CShotgun::onTake()
{
    // TODO
}

//////////////////////
FirearmKind CShotgun::getKind() { return m_kind; }
void CShotgun::setKind(FirearmKind k) { m_kind = k; }
