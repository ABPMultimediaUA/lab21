#include "ProjectileGrenade.h"

#include <cmath>
#include <iostream>

#include "WorldInstance.h"

using namespace std;

ProjectileGrenade::ProjectileGrenade()
{

}

ProjectileGrenade::ProjectileGrenade(dwe::vec3f origin, float a) :
    m_position(origin), m_angle(-a*M_PI/180), m_collides(false)
{

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
    std::cout << "Granada x: " << getPosEntity().x << " y: " << getPosition().y << " z: " << getPosEntity().z << "\n";
    /*if(!getVelocity().x==0 || !getVelocity().y==0){
        if(abs(getVelocity().x)>15 || abs(getVelocity().y)>15)
            setForce(dwe::vec2f(-getVelocity().x*0.005,-getVelocity().y*0.005));
        else if(abs(getVelocity().x)>4 && abs(getVelocity().x)<16|| abs(getVelocity().y)>4 && abs(getVelocity().y)<16)
            setForce(dwe::vec2f(-getVelocity().x*0.5,-getVelocity().y*0.5));
        //if(!getVelocity().x==0 || !getVelocity().y==0)
        else
            setVelocity(dwe::vec2f(0,0));

    }*/
}

void ProjectileGrenade::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(dwe::vec3f(m_position.x+cos(m_angle)*25.f,0,m_position.z+sin(m_angle)*25.f), box.x, box.z, m_angle, true);

    //setVelocity(dwe::vec2f(_velocity*cos(m_angle), _velocity*sin(m_angle)));
    //setForce(dwe::vec2f(_velocity*cos(m_angle)*200.0, _velocity*sin(m_angle)*200.0));
    setForce(dwe::vec2f(20, 0));
    update();
}

void ProjectileGrenade::onBeginContact(EntityPhysics* otherObject)
{
    m_collides = (otherObject && otherObject->getClassID()!=EntityPhysics::player_id);
}


