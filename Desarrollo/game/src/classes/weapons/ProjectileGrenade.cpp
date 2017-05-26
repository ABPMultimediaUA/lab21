#include "ProjectileGrenade.h"

#include <cmath>
#include <iostream>

#include "WorldInstance.h"
#include "GrenadeExplosion.h"

using namespace std;

ProjectileGrenade::ProjectileGrenade()
{
    init();
}

ProjectileGrenade::ProjectileGrenade(dwe::vec3f origin, float a) :
    m_position(origin), m_angle(-a*M_PI/180)
{
    init();
}

void ProjectileGrenade::init()
{
    m_exploding = false;
    m_exploded  = false;
    m_grenadeExplosion = 0;
    m_timeInitExplosion = 0;
    m_collides = false;

    // Parámetros de físicas
    m_damping   = 4.0f;
    m_bullet    = true;
}


ProjectileGrenade::~ProjectileGrenade()
{
    //dtor
    if (m_grenadeExplosion)
    {
        delete m_grenadeExplosion;
        m_grenadeExplosion = 0;
    }
}

bool ProjectileGrenade::getCollides(){return m_collides;}

void ProjectileGrenade::render(){};

void ProjectileGrenade::update()
{
    if (!m_exploding)
    {
        setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
        if (m_collides || (getVelocity().x == 0.0 && getVelocity().y == 0.0))
        {
            // Crear objeto explosion
            m_grenadeExplosion = GEInstance->createGrenadeExplosion(getPosition());
            m_exploding = true;
            m_timeInitExplosion = World->getTimeElapsed();
        }
    }
    else if (!m_exploded)
    {
        // Explotando
        if (World->getTimeElapsed() - m_timeInitExplosion > _timeExplosion)
            m_exploded = true;
    }
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
    m_collides = (otherObject
                && otherObject->getClassID()!=EntityPhysics::trigger_id
                && otherObject->getClassID()!=EntityPhysics::triggerSound_id
                && otherObject->getClassID()!=EntityPhysics::consumable_id
                && otherObject->getClassID()!=EntityPhysics::triggerDamage_id
                && otherObject->getClassID()!=EntityPhysics::triggerVision_id );
}


////////////////////////
void ProjectileGrenade::setPosition(dwe::vec3f p)
{
    Drawable::setPosition(p);
}

////////////////////////
bool ProjectileGrenade::getExploded()
{
    return m_exploded;
}
