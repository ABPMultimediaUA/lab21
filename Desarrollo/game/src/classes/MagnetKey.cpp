#include "MagnetKey.h"

MagnetKey::MagnetKey(int i)
{
    id=i;
    onPlayer=false;
}

MagnetKey::~MagnetKey()
{
    //dtor
}

int MagnetKey::getId()
{
    return id;
}

void MagnetKey::update()
{

}

void MagnetKey::render()
{

}
