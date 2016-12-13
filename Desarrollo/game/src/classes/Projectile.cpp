#include "Projectile.h"
#include <cmath>
#include <iostream>

using namespace std;

Projectile::Projectile()
{

}

Projectile::Projectile(int *o, float a)
{
    position[0]=o[0];
    position[1]=o[1];
    speed=5;
    angle=a*M_PI/180;
    collides=false;
}

Projectile::Projectile(int *o, int *d)
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
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::moveProjectile()
{
    if(position[0]<-10000000 || position[0]>10000000 || position[1]<-10000000 || position[1]>10000000)
        collides=true;
    if(!collides)
    {
        position[0]=position[0]+(speed*cos(angle));
        position[1]=position[1]+(speed*sin(angle));
        setPosition(dwe::vec3f(position[0],0,position[1]));
    }
}

bool Projectile::getCollides(){return collides;}

double* Projectile::getPosition(){return position;}

void Projectile::render()
{
    //Dibujar nodo
}

void Projectile::update()
{
    if(!collides){
        moveProjectile();
    }
    /*if(collides){
        delete this;
    }*/
}
