#include "Gun.h"
#include "Player.h"
#include "WorldInstance.h"

Gun::Gun()
{
    //ctor
    id=0;
}

Gun::~Gun()
{
    //dtor
}

//////////
void Gun::shoot()
{cout<<"disparo pistola"<<endl;
    Scene::Instance()->createProjectile(World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "gunBullet");
    NetInstance->sendBroadcast(ID_PROJECTILE_CREATE, World->getMainPlayer()->getPosition(), World->getMainPlayer()->getRotation().y, "gunBullet"); // Enviamos mensaje para crear projectil
}

//////////
void Gun::reload()
{
    // TODO
}
