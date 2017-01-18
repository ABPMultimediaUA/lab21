#ifndef SPEEDBOOST_H
#define SPEEDBOOST_H

#include "Consumable.h"
#include "Player.h"

class SpeedBoost : public Consumable
{
    public:
        SpeedBoost();
        virtual ~SpeedBoost();

        virtual void onTake(Player* mainPlayer);

        virtual void render() {};
        virtual void update() {};

    protected:

    private:


};

#endif // SPEEDBOOST_H
