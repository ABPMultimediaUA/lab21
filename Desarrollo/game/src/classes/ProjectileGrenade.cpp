#include "ProjectileGrenade.h"

#include <cmath>
#include <iostream>

#include "WorldInstance.h"

using namespace std;

ProjectileGrenade::ProjectileGrenade()
{

}

ProjectileGrenade::ProjectileGrenade(dwe::vec3f origin, float a)
{
    position = origin;
    speed = _velocity;
    angle = -a*M_PI/180;
    collides=false;
}


ProjectileGrenade::~ProjectileGrenade()
{
    //dtor
}

bool ProjectileGrenade::getCollides(){return collides;}

void ProjectileGrenade::render(){};

void ProjectileGrenade::update()
{
    setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
    if(!getVelocity().x==0 || !getVelocity().y==0){
        if(abs(getVelocity().x)>14 || abs(getVelocity().y)>14)
            setForce(dwe::vec2f(-getVelocity().x*0.1,-getVelocity().y*0.1));
        //if(!getVelocity().x==0 || !getVelocity().y==0)
        else{
            setForce(dwe::vec2f(-getVelocity().x*20,-getVelocity().y*20));
        }
    }

}

void ProjectileGrenade::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(dwe::vec3f(position.x+cos(angle)*25.f,0,position.z+sin(angle)*25.f), box.x, box.z, angle, true);

    setVelocity(dwe::vec2f(speed*cos(angle), speed*sin(angle)));
    update();
}

void ProjectileGrenade::onBeginContact(EntityPhysics* otherObject)
{
    collides = (otherObject && otherObject->getClassID()!=EntityPhysics::player_id);
}


