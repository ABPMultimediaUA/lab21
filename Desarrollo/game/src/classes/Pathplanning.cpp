#include "Pathplanning.h"


Pathplanning::Pathplanning()
{
    //ctor
}

Pathplanning::~Pathplanning()
{
    //dtor
}





















void Pathplanning::behaviour(Drawable* mainPlayer, Humanoid* enemyHumanoid, dwe::Node* fovnode, bool danyo)
{
    float movX = 0.0;
    float movZ = 0.0;
    float speed = enemyHumanoid->getSpeed();

    if(!danyo)  //seguimos y no hay danyo
    {
        //rotaciones
        if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x && (enemyHumanoid->getPosition().z<mainPlayer->getPosition().z+1 && enemyHumanoid->getPosition().z>mainPlayer->getPosition().z-1))
        {
            enemyHumanoid->setRotation(dwe::vec3f(0, 0.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }
        else if(enemyHumanoid->getPosition().z<mainPlayer->getPosition().z && (enemyHumanoid->getPosition().x<mainPlayer->getPosition().x+1 && enemyHumanoid->getPosition().x>mainPlayer->getPosition().x-1))
        {
            enemyHumanoid->setRotation(dwe::vec3f(0, 270.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }
        else if(enemyHumanoid->getPosition().x>mainPlayer->getPosition().x && (enemyHumanoid->getPosition().z<mainPlayer->getPosition().z+1 && enemyHumanoid->getPosition().z>mainPlayer->getPosition().z-1))
        {
            enemyHumanoid->setRotation(dwe::vec3f(0, 180.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }
        else if(enemyHumanoid->getPosition().z>mainPlayer->getPosition().z && (enemyHumanoid->getPosition().x<mainPlayer->getPosition().x+1 && enemyHumanoid->getPosition().x>mainPlayer->getPosition().x-1))
        {
            enemyHumanoid->setRotation(dwe::vec3f(0, 90.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }
        //rotaciones diagonal
        else if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x && enemyHumanoid->getPosition().z<mainPlayer->getPosition().z){
            enemyHumanoid->setRotation(dwe::vec3f(0, 315.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }
        else if(enemyHumanoid->getPosition().x>mainPlayer->getPosition().x && enemyHumanoid->getPosition().z>mainPlayer->getPosition().z){
            enemyHumanoid->setRotation(dwe::vec3f(0, 135.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }
        else if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x && enemyHumanoid->getPosition().z>mainPlayer->getPosition().z){
            enemyHumanoid->setRotation(dwe::vec3f(0, 45.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }
        else if(enemyHumanoid->getPosition().x>mainPlayer->getPosition().x && enemyHumanoid->getPosition().z<mainPlayer->getPosition().z){
            enemyHumanoid->setRotation(dwe::vec3f(0, 225.f, 0));
            fovnode->setRotation(enemyHumanoid->getRotation());
        }



        //mientras sean menores de que las de destino y no haya danyo avanzamos sumamos
        if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x)
            movX += speed;
        else if(enemyHumanoid->getPosition().x>mainPlayer->getPosition().x)
            movX -= speed;

        if(enemyHumanoid->getPosition().z<mainPlayer->getPosition().z)
            movZ += speed;
        else if(enemyHumanoid->getPosition().z>mainPlayer->getPosition().z)
            movZ -= speed;
    }
    else // si hay daño, seguimos y no hay danyo
    {
        //prototipo, huira hasta la posicion de inicio
        //mientras sean menores de que las de destino y no haya danyo avanzamos sumamos

        if(enemyHumanoid->getPosition().x<0)
            movX += speed;
        else if(enemyHumanoid->getPosition().x>0)
            movX -= speed;

        if(enemyHumanoid->getPosition().z<-70)
            movZ += speed;
        else if(enemyHumanoid->getPosition().z>-70)
            movZ -= speed;

    }

    if (movZ!=0 || movX!= 0)
    {
        if (movZ!=0 && movX!=0)  // Movimiento diagonal
        {
            movZ = movZ*0.7;  // cos45 = 0.7
            movX = movX*0.7;
        }

        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x + movX, enemyHumanoid->getPosition().y, enemyHumanoid->getPosition().z + movZ));
    }
}
