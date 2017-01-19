#include "Perception.h"
#include "Pathplanning.h"
#include <GraphicsEngine.h>
#include "NetGame.h"
#include "PlayerMate.h"

Perception::Perception()
{
    following = false;//al principio no te ha detectado y no te sigue
}

Perception::~Perception()
{
    //dtor
}
//Pathplanning* pathp = new Pathplanning();//creo el pathplanning para usar luego

bool Perception::senses(Player* mainPlayer, Humanoid* enemyHumanoid, dwe::Node* fovnode, PathplanningTask* p)
{
    // Buscamos que player o playermate está más cerca para trabajar con él
    Drawable* player;

    float enemyX = enemyHumanoid->getPosition().x;
    float enemyZ = enemyHumanoid->getPosition().z;
    float distance = fabs(enemyX - mainPlayer->getPosition().x) + fabs(enemyZ - mainPlayer->getPosition().z);
    player = mainPlayer;

    float distanceAux;
    for(int i=0; i<NetInstance->getNumPlayerMates(); i++)
        if (NetInstance->getPlayerMate(i) != 0)
    {
        distanceAux = fabs(enemyX - NetInstance->getPlayerMate(i)->getPosition().x) + fabs(enemyZ - NetInstance->getPlayerMate(i)->getPosition().z);
        if (distanceAux < distance)
        {
            player = NetInstance->getPlayerMate(i);
            distance = distanceAux;
        }
    }




    fovnode->setPosition(enemyHumanoid->getPosition());

    if(!following)  //si no estamos siguiendo calculamos la distancia de percepcion
    {
        if(player->getAnimation() == dwe::eAnimRun)//en caso de estar en velocidad normal, la percepcion del npc sera mayor
        {
            if((sqrt (pow(enemyHumanoid->getPosition().x-player->getPosition().x, 2) + pow(enemyHumanoid->getPosition().z-player->getPosition().z, 2)))<=200)//ponemos 50 como distancia de percepcion
                following=true;//si esta dentro entonces seguimos al prota
        }
        else if(player->getAnimation() == dwe::eAnimWalk)//si estamos en sigilo, el radio sera menor
        {
            if((sqrt (pow(enemyHumanoid->getPosition().x-player->getPosition().x, 2) + pow(enemyHumanoid->getPosition().z-player->getPosition().z, 2)))<=100)//ponemos 20 como distancia de percepcion
                following=true;//si esta dentro entonces seguimos al prota
        }

        /*if(fovnode->intersects(player->getNode()->getNode()))
        {
            //cout<<"colision"<<endl;
            following=true;//aunq vayas en sigilo, si te ve, te persigue
        }*/
    }
    p->setPlayer(player);
    return (following);
        //pathp->behaviour(player, enemyHumanoid, fovnode, false);

}

