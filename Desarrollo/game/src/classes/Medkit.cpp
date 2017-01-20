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
    mainPlayer->setHealth(100);
    cout << "Vida recuperada: " << mainPlayer->getLife() << endl;
}
