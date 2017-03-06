#include "TriggerGenerator.h"

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

void TriggerGenerator::update()
{

}
