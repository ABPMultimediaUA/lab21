#include "Enemy.h"
#include "WorldInstance.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "dwVectors.h"
#include "NetGame.h"
#include "Projectile.h"
#include "TriggerDamage.h"
#include "TriggerVision.h"
#include "Scene.h"

#include <limits>

Enemy::Enemy() :
    m_speed(0.0),
    m_maxHealth(10),
    m_health(m_maxHealth),
    m_attackPower(1),
    attacking(false),
    attackTriggered(false),
    memory(false),
    m_perception(0),
    m_pathplanning(0)
{
    setClassID(EntityPhysics::enemy_id);
    closestPlayer = 0;
    // Parámetros de físicas por defecto
}

void Enemy::SetVision()
{
    m_triggerVision = new TriggerVision(this);
    Scene::Instance()->getTriggerSystem().Add(m_triggerVision);
}

Enemy::~Enemy()
{
}

void Enemy::SetPatrolPoints(dwe::vec2f p1, dwe::vec2f p2)
{
    patrol1 = p1;
    patrol2 = p2;
    currentPatrol = p1;
}

void Enemy::update()
{
    dwe::vec3f pos(EntityPhysics::getPosEntity());
    pos.y = getPosition().y;
    Drawable::setPosition(pos);
}

/////////////
float Enemy::getSpeed() { return m_speed; }
/////////////
int Enemy::getHealth() { return m_health; }
/////////////
void Enemy::resetHealth() { m_health = m_maxHealth; }


////////////
void Enemy::setNetID(unsigned int netID) { m_netID = netID; }


void Enemy::move()
{
    dwe::vec2f direction = m_pathplanning->Movement();
    setRotation(dwe::vec3f(0, dwu::calculateAngleYAxis(direction), 0));
    direction.x = direction.x * m_speed;
    direction.y = direction.y * m_speed;

    dwe::vec3f pos = EntityPhysics::getPosEntity();
    pos.y = getPosition().y;

    EntityPhysics::setVelocity(direction);
    Drawable::setPosition(pos);

    if(direction.x != 0 || direction.y != 0)
        setAnimation(dwe::eAnimEnemyWalk);
    else
        setAnimation(dwe::eAnimEnemyStand);
}

bool Enemy::Sense()
{
    return m_perception->Sense();
}

void Enemy::Hear(dwe::vec3f pos)
{
    m_perception->Hear(pos);
}

void Enemy::SeePlayer(dwe::vec3f pos)
{
    m_perception->See(pos);
}

void Enemy::SetClosestPlayer(Drawable* closest)
{
    closestPlayer = closest;
}

void Enemy::SetInAttackRange(bool b)
{
    attackRange = b;
}

bool Enemy::IsInAttackRange()
{
    return attackRange;
}

bool Enemy::Attack()
{
    dwe::vec3f pos(EntityPhysics::getPosEntity());
    Drawable::setPosition(dwe::vec3f(pos.x, getPosition().y, pos.z));
    if(!attacking){
        attackTime = World->getTimeElapsed();
        setAnimation(dwe::eAnimEnemyAttack);
        attacking = true;
        EntityPhysics::setVelocity(dwe::vec2f(0,0));
    }
    if(World->getTimeElapsed() - attackTime >= 0.5f){
        if(!attackTriggered){
            attackTriggered = true;
            std::cout<<"Ataque"<<std::endl;
            TriggerDamage* triggerDamage = new TriggerDamage(getPosition(), 1.3, m_attackPower, getRotation().y);
            Scene::Instance()->getTriggerSystem().Add(triggerDamage);
        }
    }

    if(World->getTimeElapsed() - attackTime >= 1){
        std::cout<<"Fin del ataque"<<std::endl;
        setAnimation(dwe::eAnimEnemyStand);
        attacking = false;
        attackTriggered = false;
    }

    return attacking;
}

void Enemy::PlanPath()
{
    m_pathplanning->CreatePathToPosition(targetPosition);
}

bool Enemy::RouteEnd()
{
    return m_pathplanning->CheckIfRouteEnd();
}

void Enemy::ClearRoute()
{
    m_pathplanning->Clear();
}

void Enemy::SetMemory(bool b)
{
    memory = b;
}

bool Enemy::HasMemory()
{
    return memory;
}

void Enemy::SetMemoryPosition(dwe::vec2f target)
{
    memoryPosition = target;
}

dwe::vec2f Enemy::GetMemoryPosition()
{
    return memoryPosition;
}

void Enemy::SetHearing(bool b)
{
    m_perception->SetHearing(b);
}

void Enemy::SetSeeing(bool b)
{
    m_perception->SetSeeing(b);
}

void Enemy::SetSoundPosition(dwe::vec2f sound)
{
    m_perception->SetSoundPosition(sound);
}

void Enemy::SetVisionPosition(dwe::vec2f vision)
{
    m_perception->SetVisionPosition(vision);
}

bool Enemy::GetHearing()
{
    m_perception->GetHearing();
}

bool Enemy::GetSeeing()
{
    m_perception->GetSeeing();
}

dwe::vec2f Enemy::GetSoundPosition()
{
    m_perception->GetSoundPosition();
}

dwe::vec2f Enemy::GetVisionPosition()
{
    m_perception->GetVisionPosition();
}

void Enemy::ChangePatrol()
{
    if(currentPatrol.x == patrol1.x && currentPatrol.y == patrol1.y)
        currentPatrol = patrol2;
    else
        currentPatrol = patrol1;
}

void Enemy::SetPatrolPosition(dwe::vec2f patrol)
{
    currentPatrol = patrol;
}

dwe::vec2f Enemy::GetPatrolPosition()
{
    return currentPatrol;
}

void Enemy::SetTargetPosition(dwe::vec2f target)
{
    targetPosition = target;
}

dwe::vec2f Enemy::GetTargetPosition()
{
    return targetPosition;
}

/////////////
void Enemy::setNode(dwe::Node* n)
{
    Drawable::setNode(n);
    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(getPosition(), box.x, box.z, 0.0f, 10000.0f);
}
/////////////
void Enemy::onBeginContact(EntityPhysics* otherObject)
{
    if (otherObject)
    {
        EPClassID clase = otherObject->getClassID();
        switch (clase)
        {
        case EntityPhysics::projectile_id:
            {
            Projectile* p = static_cast<Projectile*>(otherObject);
            m_health -= p->getDamage();
            }
            break;
        case EntityPhysics::grenadeExplosion_id:
            m_health-=10;
            break;
        case EntityPhysics::triggerSound_id:
            Hear(otherObject->getPosEntity());
            break;
        default: break;
        }
    }
}

////////////
void Enemy::activeEnemy(dwe::vec3f position)
{
    setPosition(dwe::vec3f(position.x, 0, position.z+150));
    resetHealth();
    setPhysicsActive(true);
    m_triggerVision->setPhysicsActive(true);

    // activar animacion parado
    setAnimation(dwe::eAnimEnemyStand);

    NetInstance->sendBroadcast(ID_ACTIVE_ENEMY, m_netID);
}

////////////
void Enemy::deactiveEnemy()
{
    setPhysicsActive(false);
    m_triggerVision->setPhysicsActive(false);

    // activar animacion de morir
    setAnimation(dwe::eAnimEnemyDeath);

    NetInstance->sendBroadcast(ID_DEACTIVE_ENEMY, m_netID);
}
