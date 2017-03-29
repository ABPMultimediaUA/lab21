#include "Hud.h"
#include "WorldInstance.h"
#include "defines.h"
#include <sstream>

using namespace std;


Hud::Hud()
{
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();

    WeaponBox     = new dwe::WeaponBox(width/10, height*6.5/8);
    HealthBox     = new dwe::HealthBox (width - width/3, height*6.7/8);

    mainPlayer    = World->getMainPlayer();
}

Hud::~Hud()
{
    //dtor
}

void Hud::draw()
{
    FirearmKind weapon  = mainPlayer->getCurrentWeaponType();
    int medkits         = mainPlayer->getNumMedkits();
    int health          = mainPlayer->getHealth();
    int maxHealth       = mainPlayer->getMaxHealth();
    int ammo            = mainPlayer->getCurrentAmmo();

   // cout << "ADAAAAA" << weapon << "asdad" << ammo << endl;

    WeaponBox->draw(weapon, ammo);

    HealthBox->draw(medkits, health, maxHealth);
}

