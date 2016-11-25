#include "CharacterController.h"

CharacterController::CharacterController()
{
    //ctor
}

CharacterController::~CharacterController()
{
    //dtor
}

///////////////
int CharacterController::getStrength(){ return m_strength; }
void CharacterController::setStrength(int s) { m_strength = s; }

///////////////
int CharacterController::getHealth() { return m_health; }
void CharacterController::setHealth(int h) { m_health = h; }
