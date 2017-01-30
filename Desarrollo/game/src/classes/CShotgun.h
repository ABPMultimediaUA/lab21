#ifndef CSHOTGUN_H
#define CSHOTGUN_H

#include <defines.h>
#include <Consumable.h>
#include "Player.h"


class CShotgun : public Consumable
{
    public:
        CShotgun();
        virtual ~CShotgun();

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

#endif // CSHOTGUN_H
