#ifndef CRIFLE_H
#define CRIFLE_H

#include <defines.h>
#include <Consumable.h>
#include "Player.h"


class CRifle : public Consumable
{
    public:
        CRifle();
        virtual ~CRifle();

        virtual void onTake(Player* mainplayer);
        virtual bool couldTake(Player* mainplayer);

        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

        virtual void render() {};
        virtual void update() {};

    protected:

    private:
        FirearmKind m_kind;

};

#endif // CRIFLE_H
