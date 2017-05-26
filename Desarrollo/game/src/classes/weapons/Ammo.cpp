#include "Ammo.h"

Ammo::Ammo()
{
    m_gunAmmo       = 12;
    m_rifleAmmo     = 30;
    m_shotgunAmmo   = 8;
    m_grenade       = 1;
}

Ammo::~Ammo()
{
    //dtor
}

void Ammo::onTake(Player* mainplayer)
{
    mainplayer->setGrenades(mainplayer->getGrenades()+m_grenade);
    mainplayer->getPlayerGun()->addAmmoBag(m_gunAmmo);
    if(mainplayer->getPlayerRifle())
        mainplayer->getPlayerRifle()->addAmmoBag(m_rifleAmmo);
    if(mainplayer->getPlayerShotgun())
        mainplayer->getPlayerShotgun()->addAmmoBag(m_shotgunAmmo);
}
