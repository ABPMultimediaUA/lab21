#include "Projectile.h"

#include <cmath>
#include <iostream>

#include "WorldInstance.h"

using namespace std;

Projectile::Projectile()
{
     setClassID(EntityPhysics::projectile_id);//rmm
}

Projectile::Projectile(dwe::vec3f origin, float a)
{
    setClassID(EntityPhysics::projectile_id);//rmm

    position = origin;
    speed = _velocity;
    angle = -a*M_PI/180;
    collides=false;
}


Projectile::~Projectile()
{
    //dtor
}

bool Projectile::getCollides(){return collides;}

void Projectile::render(){};

void Projectile::update()
{
    setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));//rmm
}

//rmm////////////
void Projectile::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(dwe::vec3f(position.x+cos(angle)*25.f,0,position.z+sin(angle)*25.f), box.x, box.z, angle, true);

    setVelocity(dwe::vec2f(speed*cos(angle), speed*sin(angle)));
    update();
}

//rmm////////////
void Projectile::onBeginContact(EntityPhysics* otherObject)
{
    collides = (otherObject
                && (otherObject->getClassID()!=EntityPhysics::player_id
                    || otherObject->getClassID()!=EntityPhysics::playermate_id) );
}


