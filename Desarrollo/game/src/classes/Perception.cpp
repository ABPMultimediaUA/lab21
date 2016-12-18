#include "Perception.h"
#include "Pathplanning.h"
#include <GraphicsEngine.h>

Perception::Perception()
{
    following=false;//al principio no te ha detectado y no te sigue
}

Perception::~Perception()
{
    //dtor
}
Pathplanning* pathp = new Pathplanning();//creo el pathplanning para usar luego

void Perception::senses(Player* mainPlayer, Humanoid* enemyHumanoid, dwe::Node* fovnode, float num){
            fovnode->setPosition(enemyHumanoid->getPosition());
            if(following==false){//si no estamos siguiendo calculamos la distancia de percepcion
                if(num==20.0){//en caso de estar en velocidad normal, la percepcion del npc sera mayor
                    if((sqrt (pow(enemyHumanoid->getPosition().x-mainPlayer->getPosition().x, 2) + pow(enemyHumanoid->getPosition().z-mainPlayer->getPosition().z, 2)))<=100)//ponemos 50 como distancia de percepcion
                        following=true;//si esta dentro entonces seguimos al prota
                }
                else if(num==5.0){//si estamos en sigilo, el radio sera menor
                    if((sqrt (pow(enemyHumanoid->getPosition().x-mainPlayer->getPosition().x, 2) + pow(enemyHumanoid->getPosition().z-mainPlayer->getPosition().z, 2)))<=50)//ponemos 20 como distancia de percepcion
                        following=true;//si esta dentro entonces seguimos al prota
                }
                /*if(fovnode->getTransformedBoundingBox().intersectsWithBox(dwe::GraphicsEngine::getTransformedBoundingBox(mainPlayer*))){
                    following=true;//aunq vayas en sigilo, si te ve, te persigue
                }*/

            }

            if (following==true){
                pathp->behaviour(mainPlayer, enemyHumanoid, fovnode, false);

            }
}

