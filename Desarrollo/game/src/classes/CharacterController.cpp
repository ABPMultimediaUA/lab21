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
    //EVADING
    if (m_isEvading)
    {
        // La velocidad se calcula cuando se llama a dash()
        // Cuenta atrás
        if (World->getTimeElapsed() - m_timeEvading > _maxEvadingTime)
            m_isEvading = false;
    }
    else
    {
        float speed;

        //SIGILO
        if(GEInstance->receiver.isKeyDown(KEY_WALK))  speed = _speedWalk;
        else                                          speed = _speedRun;

        //SPEEDBOOST
        if (m_hasSpeedBoost){
            speed = speed*3.f;
            //Cuenta atrás
            if (World->getTimeElapsed() - m_timeSpeedBoost > _maxSpeedBoostTime)
                m_hasSpeedBoost = false;
        }
        //AGACHADO
        if(GEInstance->receiver.isKeyDown(KEY_DUCK))
            speed = speed/2.f;

        //ANDAR DIAGONAL
        if(     (GEInstance->receiver.isKeyDown(KEY_RIGHT) || GEInstance->receiver.isKeyDown(KEY_LEFT))
           &&   (GEInstance->receiver.isKeyDown(KEY_UP) || GEInstance->receiver.isKeyDown(KEY_DOWN)))
            speed = speed*0.7;  // cos(45) = 0.7...

        //ANDAR HORIZONTAL
        if(GEInstance->receiver.isKeyDown(KEY_RIGHT))       m_speedX = speed;
        else if(GEInstance->receiver.isKeyDown(KEY_LEFT))   m_speedX = -speed;
        else                                                m_speedX = 0.f;

        //ANDAR VERTICAL
        if(GEInstance->receiver.isKeyDown(KEY_UP))          m_speedZ = -speed;
        else if(GEInstance->receiver.isKeyDown(KEY_DOWN))   m_speedZ = speed;
        else                                                m_speedZ = 0.f;
    }
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
    m_timeSpeedBoost = World->getTimeElapsed();
}
//SETTERS
void CharacterController::dash(){
    if(!m_isEvading && (m_speedZ || m_speedX))
    {
        // Incrementamos la velocidad actual con el dash
        m_speedZ *= _speedDash;
        m_speedX *= _speedDash;

        m_isEvading = true;
        m_timeEvading = World->getTimeElapsed();
    }
}
