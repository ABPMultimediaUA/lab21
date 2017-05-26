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

#include "dwVectors.h"

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

void Enemy::InitPoints(dwe::vec2f p1, dwe::vec2f p2)
{
    dwe::vec3f pos(getPosition());
    targetPosition = dwe::vec2f(p1);
    m_pathplanning->SetNext(targetPosition);
    SetPatrolPoints(dwe::vec2f(p1), dwe::vec2f(p2));
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
    if (m_perception)
        return m_perception->Sense();
    else
        return false;
}

void Enemy::Hear(dwe::vec3f pos)
{
    if(m_perception)
        m_perception->Hear(pos);
}

void Enemy::SeePlayer(dwe::vec3f pos)
{
    if(m_perception)
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

        dwe::vec3f plPos(m_perception->GetPositionClosestPlayer());
        dwe::vec2f dir(plPos.x - getPosition().x, plPos.z - getPosition().z);
        dwe::vec2f direction = dwu::normalizeVector(dir);
        setRotation(dwe::vec3f(0, dwu::calculateAngleYAxis(direction), 0));
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

        dwe::vec3f plPos(m_perception->GetPositionClosestPlayer());
        SeePlayer(plPos);
    }

    return attacking;
}

void Enemy::PlanPath()
{
    if (m_pathplanning)
        m_pathplanning->CreatePathToPosition(targetPosition);
}

bool Enemy::RouteEnd()
{
    if (m_pathplanning)
        return m_pathplanning->CheckIfRouteEnd();
    else
        return false;
}

void Enemy::ClearRoute()
{
    if (m_pathplanning)
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
    if (m_perception)
        m_perception->SetHearing(b);
}

void Enemy::SetSeeing(bool b)
{
    if (m_perception)
        m_perception->SetSeeing(b);
}

void Enemy::SetSoundPosition(dwe::vec2f sound)
{
    if (m_perception)
        m_perception->SetSoundPosition(sound);
}

void Enemy::SetVisionPosition(dwe::vec2f vision)
{
    if (m_perception)
        m_perception->SetVisionPosition(vision);
}

bool Enemy::GetHearing()
{
    if (m_perception)
        return m_perception->GetHearing();
    else
        return false;
}

bool Enemy::GetSeeing()
{
    if (m_perception)
        return m_perception->GetSeeing();
    else
        return false;
}

dwe::vec2f Enemy::GetSoundPosition()
{
    if (m_perception)
        return m_perception->GetSoundPosition();
    else
        return dwe::vec2f(0);
}

dwe::vec2f Enemy::GetVisionPosition()
{
    if (m_perception)
        return m_perception->GetVisionPosition();
    else
        return dwe::vec2f(0);
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
            m_health-=20;
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

    if (m_triggerVision)
        m_triggerVision->setPhysicsActive(false);

    // activar animacion de morir
    setAnimation(dwe::eAnimEnemyDeath);

    NetInstance->sendBroadcast(ID_DEACTIVE_ENEMY, m_netID);
}
