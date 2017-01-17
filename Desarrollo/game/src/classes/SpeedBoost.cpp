#include "SpeedBoost.h"

SpeedBoost::SpeedBoost(int i, Player* p)
{
    //ctor
    id = i;
    mainPlayer = p;
}

SpeedBoost::~SpeedBoost()
{
    //dtor
}

int SpeedBoost::getId()
{
    return id;
}

void SpeedBoost::update()
{
    ITimer* timer = GEInstance->getDevice()->getTimer();

    float timeStamp2 = timer->getTime();

    // Coger el boost de velocidad
    bool speedBoostTaken = false;

    bool hasSpeedBoost = mainPlayer->getHasSpeedBoost();

    if(!hasSpeedBoost)
    {
        if (this != 0)
        {
            if(mainPlayer->getNode()->intersects(this->getNode()->getNode()))
            {

                timeStamp2 = timer->getTime();

                hasSpeedBoost = true;
                mainPlayer->setHasSpeedBoost(hasSpeedBoost); //

                speedBoostTaken = true;

                mainPlayer->setSpeed(speedBoostTaken, hasSpeedBoost);

                mainPlayer->setHasSpeedBoost(hasSpeedBoost); //

                speedBoostTaken = false;

                this->removeNode();


            }
        }

    }

    mainPlayer->setSpeed(speedBoostTaken, hasSpeedBoost);

}

void SpeedBoost::render()
{

}

