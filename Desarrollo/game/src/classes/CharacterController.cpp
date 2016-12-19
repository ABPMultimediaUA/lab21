#include "CharacterController.h"

CharacterController::CharacterController()
{
    m_speedX = 0;
    m_speedZ = 0;
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

//////////////////////////
void CharacterController::readEvents()
{
    float speed;

    // si camina sigilosamente
    if(GEInstance->receiver.isKeyDown(KEY_LSHIFT))
        speed = _speedWalk;
    else
        speed = _speedRun;


    //Derecha o izquierda
    if(GEInstance->receiver.isKeyDown(KEY_KEY_D))
        m_speedX = speed;
    else if(GEInstance->receiver.isKeyDown(KEY_KEY_A))
        m_speedX = -speed;
    else
        m_speedX = 0.f;

    //Hacia delante o hacia detras
    if(GEInstance->receiver.isKeyDown(KEY_KEY_W))
        m_speedZ = speed;
    else if(GEInstance->receiver.isKeyDown(KEY_KEY_S))
        m_speedZ = -speed;
    else
        m_speedZ = 0.f;
}
float CharacterController::getSpeedX() { return m_speedX; }
float CharacterController::getSpeedZ() { return m_speedZ; }
