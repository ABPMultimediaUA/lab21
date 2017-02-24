#include "PathplanningTask.h"
#include "WorldInstance.h"
#include "Pathplanning.h"
#include "Perception.h"

PathplanningTask::PathplanningTask(Pathplanning* p, Humanoid* h/*, dwe::Node* n*/)
{
    //ctor
    path = p;
    play = World->getMainPlayer();
    hum = h;
    //no = n;
    brunning = false;
}

PathplanningTask::~PathplanningTask()
{
    //dtor
}

States PathplanningTask::run()
{
    path->behaviour(play, hum,/* no, */false);
    return success;
}

void PathplanningTask::setPlayer(Drawable* pl)
{
    play = pl;
}
