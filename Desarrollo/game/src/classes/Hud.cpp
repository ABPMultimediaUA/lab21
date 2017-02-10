#include "Hud.h"

Hud::Hud()
{


}

Hud::~Hud()
{
    //dtor
}

void Hud::draw()
{

   GEInstance->addMessageLine(L"Partida iniciada");
}
