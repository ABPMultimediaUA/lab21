#include "Hud.h"
#include <sstream>
using namespace std;


Hud::Hud()
{
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();

    WeaponBox = new dwe::WeaponBox(width/10, height*6.5/8);
    HealthBox = new dwe::HealthBox (width - width/3, height*6.7/8);
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

