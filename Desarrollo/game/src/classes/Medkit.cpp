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
    mainPlayer->addMedkits(1);
    //cout << "posicion player " << mainPlayer->getPosition().x << " " << mainPlayer->getPosition().y << " " << mainPlayer->getPosition().z << endl;
}
