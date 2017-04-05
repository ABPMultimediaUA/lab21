#include "TriggerGenerator.h"
#include "WorldInstance.h"
#include "Player.h"

TriggerGenerator::TriggerGenerator()
{
    //ctor
}

TriggerGenerator::~TriggerGenerator()
{
    //dtor
}

void TriggerGenerator::triggered(Entity *e)
{
    ((Generator*)e)->activateGenerator();
}

void TriggerGenerator::render()
{

}

void TriggerGenerator::update(Entity *e)
{
    if(World->getMainPlayer()->getMKey(((Generator*)e)->getNum()))
        triggered(e);
}
