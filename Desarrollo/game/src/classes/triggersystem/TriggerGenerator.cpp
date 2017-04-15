#include "TriggerGenerator.h"
#include "WorldInstance.h"
#include "Player.h"
#include <iostream>

using namespace std;

TriggerGenerator::TriggerGenerator()
{
    //ctor
}

TriggerGenerator::~TriggerGenerator()
{
    //dtor
}

void TriggerGenerator::triggered(Generator *g)
{
    if(!g->getIsActive())
    {
        g->activateGenerator();
        cout<<"GENERATOR "<<g->getNum()<<" ACTIVATED"<<endl;
    }
}

void TriggerGenerator::render()
{

}

void TriggerGenerator::update(Generator *g)
{
    /*if(m_touchingMainPlayer && World->getMainPlayer()->getMKey(g->getNum()) && GEInstance->receiver.isKeyDown(KEY_OPEN_DOOR))
        triggered(g);*/
}
