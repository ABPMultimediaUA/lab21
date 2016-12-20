#include "Projectile.h"

#include <cmath>
#include <iostream>

#include "WorldInstance.h"

using namespace std;

Projectile::Projectile()
{
     setClassID(CLASS_PROJECTILE_ID);//rmm
}

Projectile::Projectile(int *o, float a)
{
    setClassID(CLASS_PROJECTILE_ID);//rmm

    position[0]=o[0];
    position[1]=o[1];
    speed=3.f;//25.f;
    angle=a*M_PI/180;
    collides=false;

    contador = 0;
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
    contador++;
    //if(position[0]<-1000 || position[0]>100 || position[1]<-100 || position[1]>100)
    if(contador>100)
        collides=true;
    if(!collides)
    {
        position[0]=position[0]+(speed*cos(angle));
        position[1]=position[1]+(speed*sin(angle));
        setPosition(dwe::vec3f(position[0],0,position[1]));
        //cout<<"Posicion("<<position[0]<<","<<position[1]<<")"<<endl;
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
    //Drawable::setPosition(dwe::vec3f(getPosEntity().x, Drawable::getPosition().y, getPosEntity().z));//rmm
    /*rmm*/
    if(!collides){
        moveProjectile();
    }
    /**/
    /*if(collides){
        delete this;
    }*/
}

//rmm////////////
void Projectile::setNode(dwe::Node* n)
{
    Drawable::setNode(n);
    createDynamicBody(Drawable::getPosition());

    /*setPosition(dwe::vec3f(position[0]+cos(angle)*25.f,0,position[1]+sin(angle)*25.f));//rmm
    setPosEntity(Drawable::getPosition(), angle);//rmm
    update();//rmm
    setVelocity(dwe::vec3f(speed*cos(angle), 0, speed*sin(angle)));//rmm
    cout << "Velocidad x: " << speed*cos(angle) << " - Velocidad z: " << speed*sin(angle) << "\n";*/
}

//rmm////////////
void Projectile::onBeginContact(EntityPhysics* otherObject)
{
    collides = (otherObject && otherObject->getClassID()!=CLASS_PLAYER_ID);
    cout << "begincontact projectile\n";
}


