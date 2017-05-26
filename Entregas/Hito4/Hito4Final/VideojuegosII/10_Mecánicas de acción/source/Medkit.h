#ifndef MEDKIT_H
#define MEDKIT_H

#include "Consumable.h"
#include "Player.h"


class Medkit : public Consumable
{
    public:
        Medkit();
        virtual ~Medkit();

         virtual void onTake(Player* mainPlayer);

         virtual void render() {};
         virtual void update() {};

    protected:

    private:
};

#endif // MEDKIT_H
