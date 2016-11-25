#ifndef AMMORIFLE_H
#define AMMORIFLE_H

#include <defines.h>
#include <Ammo.h>


class AmmoRifle : public Ammo
{
    public:
        AmmoRifle();
        virtual ~AmmoRifle();

        void onTake();

        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

    protected:

    private:
        FirearmKind m_kind;
};

#endif // AMMORIFLE_H
