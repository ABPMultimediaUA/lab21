#ifndef AMMOGUN_H
#define AMMOGUN_H

#include <defines.h>
#include <Ammo.h>


class AmmoGun : public Ammo
{
    public:
        AmmoGun();
        virtual ~AmmoGun();

        virtual void onTake(Player* mainPlayer);


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
