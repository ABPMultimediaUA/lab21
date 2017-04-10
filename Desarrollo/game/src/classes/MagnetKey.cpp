#include "MagnetKey.h"
#include "WorldInstance.h"
#include "Player.h"
#include <iostream>

using namespace std;

MagnetKey::MagnetKey(int i)
{
    id=i;
}

MagnetKey::~MagnetKey()
{
    //dtor
}

void MagnetKey::onTake(Player* mainPlayer)
{
    mainPlayer->setMKeys(id);
}

int MagnetKey::getId()
{
    return id;
}
