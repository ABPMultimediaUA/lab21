#ifndef AMMORIFLE_H
#define AMMORIFLE_H

#include <defines.h>
#include <Ammo.h>
#include "Player.h"


class AmmoRifle : public Ammo
{
    public:
        AmmoRifle();
        virtual ~AmmoRifle();

        void onTake(Player* mainplayer);

        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

    protected:

    private:
        FirearmKind m_kind;
};

#endif // AMMORIFLE_H
