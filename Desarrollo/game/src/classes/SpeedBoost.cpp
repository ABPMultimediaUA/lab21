#include "SpeedBoost.h"

SpeedBoost::SpeedBoost()
{
    //ctor
}

SpeedBoost::~SpeedBoost()
{
    //dtor
}


void SpeedBoost::onTake(Player* mainPlayer)
{
    mainPlayer->setSpeedBoost();
}
