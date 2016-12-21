#include "Generator.h"

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
        active=true;
        for(int i=0; i<entities; i++)
        {
            d=(Door*)sector[i];
            d->setActive();
        }
    }
    delete d;
}

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
