#include "Enemy.h"
#include "WorldInstance.h"

Enemy::Enemy()
{
    //ctor
    m_speed = 0.0;
    setClassID(CLASS_ENEMY_ID);
    m_health=10;

}

Enemy::~Enemy()
{
    //dtor
}

/////////////
float Enemy::getSpeed() { return m_speed; }
/////////////
int Enemy::getHealth() { return m_health; }


////////////
void Enemy::setNetID(unsigned int netID) { m_netID = netID; }

/////////////
void Enemy::setPosition(dwe::vec3f p)
{
    dwe::vec3f pos(getPosEntity());
    dwe::vec3f newPos(pos.x + p.x, pos.y + p.y, pos.z + p.z);
    setPosEntity(newPos, getRotation().y);
    Drawable::setPosition(getPosEntity());
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
    if((otherObject && otherObject->getClassID()==CLASS_PROJECTILE_ID)){
        m_health-=5;
    }
}
