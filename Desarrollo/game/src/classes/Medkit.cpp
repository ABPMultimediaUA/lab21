#include "Medkit.h"

Medkit::Medkit()
{
    //ctor
}

Medkit::~Medkit()
{
    //dtor
}

/////////////

void Medkit::onTake(Player* mainPlayer)
{
    mainPlayer->setMedkits(1);
}
