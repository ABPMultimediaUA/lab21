#include "CharacterController.h"
#include "WorldInstance.h"

CharacterController::CharacterController()
{
    m_speedX = 0;
    m_speedZ = 0;
    m_speedb = false;
    m_t = 0;
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

    // insulina
    //if(GEInstance->receiver.isKeyDown(KEY_KEY_9))
    if (CharacterController::getSpeedBoost())
        speed = speed*2.f;

    // agachado
    if(GEInstance->receiver.isKeyDown(KEY_KEY_8))
        speed = speed/2.f;

    // Si va en diagonal, reducimos velocidad
    if((GEInstance->receiver.isKeyDown(KEY_KEY_D) || GEInstance->receiver.isKeyDown(KEY_KEY_A))
       && (GEInstance->receiver.isKeyDown(KEY_KEY_W) || GEInstance->receiver.isKeyDown(KEY_KEY_S)))
        speed = speed*0.7;  // cos(45) = 0.7...

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

void CharacterController::setSpeed(bool &a, bool &b)
{

    //ITimer* timer = GEInstance->getDevice()->getTimer();


    float time;


    if (a) // Si acabo de cogerlo
        m_t = World->getTimeElapsed();//timer->getTime();

    else if (b) // Si cogí el boost
    {
        time = World->getTimeElapsed();//timer->getTime();
       if ((time - m_t) <= 5000.0)
        {
            m_speedb = true;
            //cout << "CORRO RAPIDO" << endl;
            //cout << "tiempo t " << m_t << endl;
            //cout << "tiempo time " << time << endl;
        }
        else
        {
            //cout << "LENTO" << endl;
            m_speedb = false;
            a = false;
            b = false;
        }
    }
    else
        m_speedb = false;



}


bool CharacterController::getSpeedBoost()
{
    return m_speedb;
}

