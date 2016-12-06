#include "Pathplanning.h"
#include "math.h"

Pathplanning::Pathplanning()
{
    //ctor
    following=false;//al principio no te ha detectado y no te sigue
}

Pathplanning::~Pathplanning()
{
    //dtor
}

void Pathplanning::behaviour(Player* mainPlayer, Humanoid* enemyHumanoid, float num){
    if(following==false){//si no estamos siguiendo calculamos la distancia de percepcion
                if(num==10.0){//en caso de estar en velocidad normal, la percepcion del npc sera mayor
                    if((sqrt (pow(enemyHumanoid->getPosition().x-mainPlayer->getPosition().x, 2) + pow(enemyHumanoid->getPosition().z-mainPlayer->getPosition().z, 2)))<=100)//ponemos 50 como distancia de percepcion
                        following=true;//si esta dentro entonces seguimos al prota
                }
                else if(num==2.0){//si estamos en sigilo, el radio sera menor
                    if((sqrt (pow(enemyHumanoid->getPosition().x-mainPlayer->getPosition().x, 2) + pow(enemyHumanoid->getPosition().z-mainPlayer->getPosition().z, 2)))<=50)//ponemos 20 como distancia de percepcion
                        following=true;//si esta dentro entonces seguimos al prota
                }

            }
            if(following==true){
                if(enemyHumanoid->getPosition().x<mainPlayer->getPosition().x || enemyHumanoid->getPosition().z<mainPlayer->getPosition().z || enemyHumanoid->getPosition().x>mainPlayer->getPosition().x || enemyHumanoid->getPosition().z>mainPlayer->getPosition().z/*) && danyo==0*/){ //mientras sean menores de que las de destino y no haya danyo avanzamos sumamos
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
                    //cout<<"aun no"<<endl;
                }
            }
}
