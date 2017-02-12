#include "Hud.h"


Hud::Hud(dwe::GraphicsEngine::GETexture* t)
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
