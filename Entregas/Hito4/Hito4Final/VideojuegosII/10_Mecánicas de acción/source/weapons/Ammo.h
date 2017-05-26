#ifndef AMMO_H
#define AMMO_H

#include <Consumable.h>
#include "Player.h"


class Ammo : public Consumable
{
    public:
        Ammo();
        virtual ~Ammo();

        void update(){};
        void render(){};

        void onTake(Player* mainplayer);

    protected:

    private:
        int m_gunAmmo;
        int m_rifleAmmo;
        int m_shotgunAmmo;
        int m_grenade;
};

#endif // AMMO_H
