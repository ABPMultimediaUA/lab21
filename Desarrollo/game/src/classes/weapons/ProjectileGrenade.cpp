#include "ProjectileGrenade.h"

#include <cmath>
#include <iostream>

#include "WorldInstance.h"

using namespace std;

ProjectileGrenade::ProjectileGrenade()
{
    init();
}

ProjectileGrenade::ProjectileGrenade(dwe::vec3f origin, float a) :
    m_position(origin), m_angle(-a*M_PI/180), m_collides(false)
{
    init();
}

void ProjectileGrenade::init()
{
    // Parámetros de físicas
    m_damping   = 4.0f;
    m_bullet    = true;
}


ProjectileGrenade::~ProjectileGrenade()
{
    //dtor
}

bool ProjectileGrenade::getCollides(){return m_collides;}

void ProjectileGrenade::render(){};

void ProjectileGrenade::update()
{
    setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
}

void ProjectileGrenade::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(dwe::vec3f(m_position.x+cos(m_angle)*25.f,0,m_position.z+sin(m_angle)*25.f), box.x, box.z, m_angle);

    setImpulse(dwe::vec2f(_impulse*cos(m_angle), _impulse*sin(m_angle)));
    update();
}

void ProjectileGrenade::onBeginContact(EntityPhysics* otherObject)
{
    m_collides = (otherObject && otherObject->getClassID()!=EntityPhysics::player_id);
}


////////////////////////
void ProjectileGrenade::setPosition(dwe::vec3f p)
{
    Drawable::setPosition(p);
}

