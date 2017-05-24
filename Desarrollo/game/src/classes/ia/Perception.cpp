#include "Perception.h"
#include "Enemy.h"
#include "NetGame.h"
#include "PlayerMate.h"
#include "WorldInstance.h"

#include "dwVectors.h"

Perception::Perception(Enemy *owner)
{
    m_owner = owner;
    m_hearing = false;
    m_seeing = false;
}

Perception::~Perception()
{
    //dtor
}

void Perception::Hear(dwe::vec3f pos)
{
    m_hearing = true;
    m_soundPosition = dwe::vec2f(pos.x, pos.z);
}

void Perception::See(dwe::vec3f pos)
{
    m_seeing = true;
    m_visionPosition = dwe::vec2f(pos.x, pos.z);
}

bool Perception::Sense()
{
    Drawable* player = World->getMainPlayer();

    if(m_hearing){
        m_owner->SetMemoryPosition(m_soundPosition);
        m_owner->SetMemory(true);
        m_hearing = false;
    }

    float distance = GetDistanceClosestPlayer(player);

    //m_owner->SetClosestPlayer(player);

    if(distance<=1837){
        m_owner->SetInAttackRange(true);}
    else{
        m_owner->SetInAttackRange(false);}

    if(m_seeing)
    {
        m_owner->SetMemoryPosition(m_visionPosition);
        m_owner->SetMemory(true);
        m_seeing = false;
        return true;
    }
    return false;
}

float Perception::GetDistanceClosestPlayer(Drawable*& pl)
{
    dwe::vec3f enemyPos(m_owner->getPosition());                    dwe::vec2f ePos(enemyPos.x, enemyPos.z);
    dwe::vec3f playerPos(World->getMainPlayer()->getPosition());    dwe::vec2f pPos(playerPos.x, playerPos.z);

    float distance = dwu::calculateSquaredDistance(ePos, pPos);
    float distanceAux;

    for(int i=0; i<NetInstance->getNumPlayerMates(); i++){
        Drawable *playerMate = NetInstance->getPlayerMate(i);
        if (playerMate != 0)
        {
            dwe::vec3f playerPos(playerMate->getPosition());     dwe::vec2f pPos(playerPos.x, playerPos.z);
            distanceAux = dwu::calculateSquaredDistance(ePos, pPos);
            if (distanceAux < distance)
            {
                pl = playerMate;
                distance = distanceAux;
            }
        }
    }
    return distance;
}
