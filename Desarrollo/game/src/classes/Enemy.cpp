#include "Enemy.h"

Enemy::Enemy()
{
    //ctor
    m_speed = 0.0;
}

Enemy::~Enemy()
{
    //dtor
}

/////////////
float Enemy::getSpeed() { return m_speed; }
