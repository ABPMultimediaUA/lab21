#include "Succeeder.h"

Succeeder::Succeeder()
{
    brunning = false;
}

Succeeder::~Succeeder()
{
    //dtor
}

void Succeeder::addChild (Node* ch)
{
    child = ch;
}


States Succeeder::run()
{
    if(child->run() == running){
        brunning = true;
        return running;
    }
    brunning = false;
    return success;
}
