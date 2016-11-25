#ifndef AMMOGUN_H
#define AMMOGUN_H

#include <defines.h>
#include <Ammo.h>


class AmmoGun : public Ammo
{
    public:
        AmmoGun();
        virtual ~AmmoGun();

        void onTake();


        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

    protected:

    private:
        FirearmKind m_kind;
};

#endif // AMMOGUN_H
