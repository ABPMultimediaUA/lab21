#include "Hud.h"
#include "WorldInstance.h"
#include "defines.h"
#include <sstream>
#include "GUI.h"

using namespace std;


Hud::Hud()
{
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();

    WeaponBox     = new dwe::WeaponBox(25, height*6/8);
    HealthBox     = new dwe::HealthBox (width - 200 - 25, height*6.7/8);

    mainPlayer    = World->getMainPlayer();
}

Hud::~Hud()
{
    delete WeaponBox;
    delete HealthBox;
}

void Hud::draw()
{
    FirearmKind weapon  = mainPlayer->getCurrentWeaponType();
    int medkits         = mainPlayer->getNumMedkits();
    int health          = mainPlayer->getHealth();
    int maxHealth       = mainPlayer->getMaxHealth();
    int ammo            = mainPlayer->getCurrentWeapon()->getAmmo();
    int ammoBag         = mainPlayer->getCurrentWeapon()->getAmmoBag();
    int grenades        = mainPlayer->getGrenades();
    int speedBoosts     = mainPlayer->getSpeedBoosts();

    WeaponBox->draw(weapon, ammo, ammoBag, grenades);

    HealthBox->draw(medkits, health, maxHealth, speedBoosts);
}

