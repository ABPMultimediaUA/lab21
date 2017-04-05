#include "Generator.h"
#include "NetGame.h"

Generator::Generator(int n, bool b)
{
    num=n;
    active=b;
    entities=0;
    sector=new Entity*[entities];
}

Generator::~Generator()
{
    delete[] sector;
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
    if(!active)
    {
        //Generador desactivado
        //Dibujar nodo
    }
    else
    {
        //Generador activado
        //Dibujar nodo
    }
}

void Generator::update()
{
    if(active){
        //Hacer ruidos y cosas
    }
}

void Generator::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f s = n->getBoundingBox();
    createStaticBody(getPosition(), s.x, s.z, 90);
}

void Generator::setPosition(dwe::vec3f p)
{
    setPosEntity(p, getRotation().y);
    Drawable::setPosition(p);
}
