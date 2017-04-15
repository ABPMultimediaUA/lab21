#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "DrawablePhysics.h"

class Player;

class Consumable : public DrawablePhysics
{
    public:
        Consumable();
        virtual ~Consumable();

        virtual void onTake(Player* mainPlayer) = 0;

        bool getIsTaken();
        virtual void update(Player* mainPlayer);
        void take();   // Marca como ya cogido y quita nodo como en update
        void setNetID(unsigned int netID);

        virtual void setNode(dwe::Node* n);

        virtual void onBeginContact(EntityPhysics* otherObject);
        virtual void onEndContact(EntityPhysics* otherObject);

    protected:
        int m_netID;
        bool m_touchingMainPlayer;

    private:
        bool m_isTaken;
};

#endif // CONSUMABLE_H
