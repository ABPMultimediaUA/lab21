#ifndef GRENADE_H
#define GRENADE_H

#include <Weapon.h>


class Grenade : public Weapon
{
    public:
        Grenade();
        virtual ~Grenade();

        void shoot();

    protected:

    private:
};

#endif // GRENADE_H
