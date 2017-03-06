#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include <Drawable.h>

class Player;

class Consumable : public Drawable
{
    public:
        Consumable();
        virtual ~Consumable();

        virtual void onTake(Player* mainPlayer) = 0;

        bool getIsTaken();
        virtual void update(Player* mainPlayer);
        void take();   // Marca como ya cogido y quita nodo como en update
        void setNetID(unsigned int netID);

    protected:
        int m_netID;

    private:
        bool m_isTaken;
};

#endif // CONSUMABLE_H
