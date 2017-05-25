#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Drawable.h"

class Player;
class TriggerConsumable;

class Consumable : public Drawable
{
    public:

        Consumable();

        virtual ~Consumable();

        virtual void onTake(Player* mainPlayer) = 0;
        virtual bool couldTake(Player* mainPlayer);

        bool getIsTaken();
        virtual void Take();
        void update(Player* mainPlayer){};
        void take();   // Marca como ya cogido y quita nodo como en update
        void setNetID(unsigned int netID);

        virtual void setNode(dwe::Node* n);
        virtual void setPosition(dwe::vec3f p);

    protected:

        unsigned int m_netID;

    private:

        TriggerConsumable* m_trigger;
        bool m_isTaken;
};

#endif // CONSUMABLE_H
