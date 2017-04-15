#include "Generator.h"
#include "NetGame.h"
#include "Door.h"
#include "AudioEngine.h"

Generator::Generator(int n, bool b)
{
    num=n;
    active=b;
    entities=0;
    sector=new Entity*[entities];

    // Parámetros de físicas por defecto
}

Generator::~Generator()
{

}

void Generator::setSector(Entity **s, int e)
{
    entities=e;
    sector=new Entity*[entities];
    for(int i=0; i<entities; i++){
        sector[i]=s[i];
    }
}

void Generator::activateGenerator()
{
    Door *d;
    if(!active)
    {
        AEInstance->Play2D("media/AccesoDenegado.wav");
        NetInstance->sendBroadcast(ID_GENERATOR_ACTIVE, m_netID);

        active=true;
        for(int i=0; i<entities; i++)
        {
            d=(Door*)sector[i];
            d->setActive();
        }
    }
}

int Generator::getNum(){ return num; }

bool Generator::getIsActive(){ return active; }

void Generator::render()
{

}

void Generator::update()
{

}

void Generator::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f s = n->getBoundingBox();
    createStaticBody(getPosition(), s.x, s.z, 90);
}

