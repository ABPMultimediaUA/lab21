#include "CharacterController.h"
#include "WorldInstance.h"
#include "Player.h"

CharacterController::CharacterController()
{
    m_speedX = 0;
    m_speedZ = 0;
    m_hasSpeedBoost = false;
    m_isEvading = false;
    m_t = 0;
}

CharacterController::~CharacterController()
{
    //dtor
}

/////////////////////////////////////////////////////////////////////////
/////////////////////        READ EVENTS         ////////////////////////
/////////////////////////////////////////////////////////////////////////
void CharacterController::readEvents()
{
    float speed;

    //SIGILO
    if(GEInstance->receiver.isKeyDown(KEY_LSHIFT))  speed = _speedWalk;
    else                                            speed = _speedRun;

    //SPEEDBOOST
    if (m_hasSpeedBoost){
        speed = speed*2.f;
        //Cuenta atrás
        if (World->getTimeElapsed() - m_timeSpeedBost > _maxSpeedBostTime)
            m_hasSpeedBoost = false;
    }
    //EVADING
    if (m_isEvading){
        speed = _speedDash;
        //Cuenta atrás
        if (World->getTimeElapsed() - m_timeEvading > _maxEvadingTime){
            m_isEvading = false;
        }
    }

    //AGACHADO
    if(GEInstance->receiver.isKeyDown(KEY_KEY_8))
        speed = speed/2.f;

    //ANDAR DIAGONAL
    if(     (GEInstance->receiver.isKeyDown(KEY_KEY_D) || GEInstance->receiver.isKeyDown(KEY_KEY_A))
       &&   (GEInstance->receiver.isKeyDown(KEY_KEY_W) || GEInstance->receiver.isKeyDown(KEY_KEY_S)))
        speed = speed*0.7;  // cos(45) = 0.7...

    //ANDAR HORIZONTAL
    if(GEInstance->receiver.isKeyDown(KEY_KEY_D))           m_speedX = speed;
    else if(GEInstance->receiver.isKeyDown(KEY_KEY_A))      m_speedX = -speed;
    else                                                    m_speedX = 0.f;

    //ANDAR VERTICAL
    if(GEInstance->receiver.isKeyDown(KEY_KEY_W))           m_speedZ = -speed;
    else if(GEInstance->receiver.isKeyDown(KEY_KEY_S))      m_speedZ = speed;
    else                                                    m_speedZ = 0.f;

}


//GETTERS
float CharacterController::getSpeedX() { return m_speedX; }
float CharacterController::getSpeedZ() { return m_speedZ; }
///////////////
int CharacterController::getStrength(){ return m_strength; }
void CharacterController::setStrength(int s) { m_strength = s; }
///////////////
int CharacterController::getHealth() { return m_health; }
void CharacterController::setHealth(int h) { m_health = h; }


//SETTERS
void CharacterController::setSpeedBoost(){
    m_hasSpeedBoost = true;
    m_timeSpeedBost = World->getTimeElapsed();
}
//SETTERS
void CharacterController::dash(){
    m_isEvading = true;
    m_timeEvading = World->getTimeElapsed();
}
