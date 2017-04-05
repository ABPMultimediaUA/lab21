#ifndef AMMOGRENADE_H
#define AMMOGRENADE_H

#include <Ammo.h>


class AmmoGrenade : public Ammo
{
    public:
        AmmoGrenade();
        virtual ~AmmoGrenade();

        void onTake();

    protected:

    private:
};

#endif // AMMOGRENADE_H
