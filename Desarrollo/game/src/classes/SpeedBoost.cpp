#include "SpeedBoost.h"

SpeedBoost::SpeedBoost(int i, Player* p)
{
    //ctor
    id = i;
    mainPlayer = p;
    hasSpeedBoost = false;
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



    // Coger el boost de velocidad
    bool speedBoostTaken = false;

    hasSpeedBoost = mainPlayer->getHasSpeedBoost();

    if(!hasSpeedBoost)
    {
        if (this->getNode() != 0)
        {
            if(mainPlayer->getNode()->intersects(this->getNode()->getNode()))
            {

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

    mainPlayer->setHasSpeedBoost(hasSpeedBoost); //

}

void SpeedBoost::render()
{

}

