#ifndef AMMOSHOTGUN_H
#define AMMOSHOTGUN_H

#include <defines.h>
#include <Ammo.h>


class AmmoShotgun : public Ammo
{
    public:
        AmmoShotgun();
        virtual ~AmmoShotgun();

        void onTake();

        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

    protected:

    private:
        FirearmKind m_kind;
};

#endif // AMMOSHOTGUN_H
