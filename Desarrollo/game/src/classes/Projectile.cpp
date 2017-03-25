#include "Projectile.h"

#include <cmath>
#include <iostream>

#include "WorldInstance.h"

using namespace std;

Projectile::Projectile()
{
     setClassID(CLASS_PROJECTILE_ID);//rmm
}

Projectile::Projectile(dwe::vec3f origin, float a)
{
    setClassID(CLASS_PROJECTILE_ID);//rmm

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

    setVelocity(dwe::vec3f(speed*cos(angle), 0, speed*sin(angle)));
    update();
}

//rmm////////////
void Projectile::onBeginContact(EntityPhysics* otherObject)
{
    collides = (otherObject && otherObject->getClassID()!=CLASS_PLAYER_ID);
}


