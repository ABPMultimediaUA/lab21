#include "Hud.h"
#include <sstream>
using namespace std;


Hud::Hud()
{
    WeaponBox = new dwe::WeaponBox(SCREEN_WIDTH/10, SCREEN_HEIGHT*6.5/8);
    HealthBox = new dwe::HealthBox (SCREEN_WIDTH - SCREEN_WIDTH/3, SCREEN_HEIGHT*6.7/8);
}

Hud::~Hud()
{
    //dtor
}

void Hud::draw()
{
    WeaponBox->draw();

    HealthBox->draw();
}

