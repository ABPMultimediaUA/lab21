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
    //contador = 0;
}

/*Projectile::Projectile(int *o, int *d)
{
    int origin[2], destination[2];
    origin[0]=o[0];
    origin[1]=o[1];
    destination[0]=d[0];
    destination[1]=d[1];
    speed=5;
    position[0]=origin[0];
    position[1]=origin[1];
    angle=atan2(destination[1] - origin[1], destination[0] - origin[0]);
    collides=false;
}*/

Projectile::~Projectile()
{
    //dtor
}

bool Projectile::getCollides(){return collides;}

void Projectile::render(){};

void Projectile::update()
{
    setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));//rmm
    //rmm if(!collides){moveProjectile();}
}

//rmm////////////
void Projectile::setNode(dwe::Node* n)
{
    Drawable::setNode(n);
    createDynamicBody(dwe::vec3f(position.x+cos(angle)*25.f,0,position.z+sin(angle)*25.f), angle, true);

    setVelocity(dwe::vec3f(speed*cos(angle), 0, speed*sin(angle)));
    update();
    //cout << "Velocidad x: " << speed*cos(angle) << " - Velocidad z: " << speed*sin(angle) << "\n";
}

//rmm////////////
void Projectile::onBeginContact(EntityPhysics* otherObject)
{
    collides = (otherObject && otherObject->getClassID()!=CLASS_PLAYER_ID);
}


