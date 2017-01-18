#ifndef SPEEDBOOST_H
#define SPEEDBOOST_H

#include "Entity.h"
#include "Player.h"

class SpeedBoost : public Entity
{
    public:

        SpeedBoost(int i, Player* p);

        virtual ~SpeedBoost();

        int getId();

        virtual void render();

        virtual void update();


    protected:

    private:

        int id;
        Player* mainPlayer;
        bool hasSpeedBoost;


};

#endif // SPEEDBOOST_H
