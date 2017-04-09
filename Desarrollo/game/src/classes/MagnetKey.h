#ifndef MAGNETKEY_H
#define MAGNETKEY_H

#include "Consumable.h"
#include "Player.h"


class MagnetKey: public Consumable
{
    public:
        MagnetKey(int i);
        virtual ~MagnetKey();

        virtual void onTake(Player* mainPlayer);
        int getId();

        virtual void render() {};
        virtual void update() {};

    protected:

    private:
        int id;
};

#endif // MAGNETKEY_H
