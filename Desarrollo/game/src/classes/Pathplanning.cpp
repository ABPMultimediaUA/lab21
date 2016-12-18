#include "Pathplanning.h"

Pathplanning::Pathplanning()
{
    //ctor
}

Pathplanning::~Pathplanning()
{
    //dtor
}

void Pathplanning::behaviour(Player* mainPlayer, Humanoid* enemyHumanoid, dwe::Node* fovnode, bool danyo){
            if(danyo==false){//seguimos y no hay danyo
                if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x || enemyHumanoid->getPosition().z<mainPlayer->getPosition().z || enemyHumanoid->getPosition().x>mainPlayer->getPosition().x || enemyHumanoid->getPosition().z>mainPlayer->getPosition().z){ //mientras sean menores de que las de destino y no haya danyo avanzamos sumamos
                    if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x){
                        //posNodo.setX(posNodo.getx()+1);
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x+0.1,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z));
                    }
                    if(enemyHumanoid->getPosition().z<mainPlayer->getPosition().z){
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z+0.1));
                    }
                    if(enemyHumanoid->getPosition().x>mainPlayer->getPosition().x){
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x-0.1,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z));
                    }

                    if(enemyHumanoid->getPosition().z>mainPlayer->getPosition().z){
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z-0.1));
                    }
                }
                //rotaciones
                    if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x && (enemyHumanoid->getPosition().z<mainPlayer->getPosition().z+1 && enemyHumanoid->getPosition().z>mainPlayer->getPosition().z-1)){
                        enemyHumanoid->setRotation(dwe::vec3f(0, 0.f, 0));
                        fovnode->setRotation(enemyHumanoid->getRotation());
                    }
                    else if(enemyHumanoid->getPosition().z<mainPlayer->getPosition().z && (enemyHumanoid->getPosition().x<mainPlayer->getPosition().x+1 && enemyHumanoid->getPosition().x>mainPlayer->getPosition().x-1)){
                        //node2->setPosition(core::vector3df(node2->getPosition().X,node2->getPosition().Y,node2->getPosition().Z+0.02));
                        enemyHumanoid->setRotation(dwe::vec3f(0, 270.f, 0));
                        fovnode->setRotation(enemyHumanoid->getRotation());
                    }
                    else if(enemyHumanoid->getPosition().x>mainPlayer->getPosition().x && (enemyHumanoid->getPosition().z<mainPlayer->getPosition().z+1 && enemyHumanoid->getPosition().z>mainPlayer->getPosition().z-1)){
                        //node2->setPosition(core::vector3df(node2->getPosition().X-0.02,node2->getPosition().Y,node2->getPosition().Z));
                        enemyHumanoid->setRotation(dwe::vec3f(0, 180.f, 0));
                        fovnode->setRotation(enemyHumanoid->getRotation());
                    }
                    else if(enemyHumanoid->getPosition().z>mainPlayer->getPosition().z && (enemyHumanoid->getPosition().x<mainPlayer->getPosition().x+1 && enemyHumanoid->getPosition().x>mainPlayer->getPosition().x-1)){
                        //node2->setPosition(core::vector3df(node2->getPosition().X,node2->getPosition().Y,node2->getPosition().Z-0.02));
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
            }
            else if(danyo==true){//seguimos y no hay danyo
                    //prototipo, huira hasta la posicion de inicio
                if(enemyHumanoid->getPosition().x<0 || enemyHumanoid->getPosition().z<-70 || enemyHumanoid->getPosition().x>0 || enemyHumanoid->getPosition().z>-70/*) && danyo==0*/){ //mientras sean menores de que las de destino y no haya danyo avanzamos sumamos
                    if(enemyHumanoid->getPosition().x<0){
                        //posNodo.setX(posNodo.getx()+1);
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x+0.1,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z));
                    }
                    if(enemyHumanoid->getPosition().z<-70){
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z+0.1));
                    }
                    if(enemyHumanoid->getPosition().x>0){
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x-0.1,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z));
                    }

                    if(enemyHumanoid->getPosition().z>-70){
                        enemyHumanoid->setPosition(dwe::vec3f(enemyHumanoid->getPosition().x,enemyHumanoid->getPosition().y,enemyHumanoid->getPosition().z-0.1));
                    }
                }
            }
}
