#ifndef AMMOGUN_H
#define AMMOGUN_H

#include <defines.h>
#include <Ammo.h>
#include "Player.h"


class AmmoGun : public Ammo
{
    public:
        AmmoGun();
        virtual ~AmmoGun();

        virtual void onTake(Player* mainplayer);


        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

        virtual void render() {};
        virtual void update() {};

    protected:

    private:
        FirearmKind m_kind;
};

#endif // AMMOGUN_H
