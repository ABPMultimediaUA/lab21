#include "Enemy.h"
#include "WorldInstance.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "dwVectors.h"

Enemy::Enemy() :
    m_speed(0.0),
    m_maxHealth(10),
    m_health(m_maxHealth),
    m_perception(0),
    m_pathplanning(0)
{
    setClassID(EntityPhysics::enemy_id);

    // Parámetros de físicas por defecto
}

Enemy::~Enemy()
{
    //dtor
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
}

bool Enemy::Sense()
{
    return m_perception->Sense();
}

void Enemy::PlanPath()
{
    m_pathplanning->CreatePathToPosition(targetPosition);
}

void Enemy::SetTargetPosition(dwe::vec2f target)
{
    targetPosition = target;
}

/////////////
void Enemy::setNode(dwe::Node* n)
{
    Drawable::setNode(n);
    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(getPosition(), box.x, box.z);
}
/////////////
void Enemy::onBeginContact(EntityPhysics* otherObject)
{
    if((otherObject && otherObject->getClassID()==EntityPhysics::projectile_id)){
        m_health-=5;
    }
}
