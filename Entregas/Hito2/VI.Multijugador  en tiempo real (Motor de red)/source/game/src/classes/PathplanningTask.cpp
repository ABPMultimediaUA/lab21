#include "PathplanningTask.h"

PathplanningTask::PathplanningTask(Pathplanning* p, Drawable* pl, Humanoid* h, dwe::Node* n)
{
    //ctor
    path = p;
    play = pl;
    hum = h;
    no = n;
    brunning = false;
}

PathplanningTask::~PathplanningTask()
{
    //dtor
}

States PathplanningTask::run()
{
    path->behaviour(play, hum, no, false);
    return success;
}

void PathplanningTask::setPlayer(Drawable* pl)
{
    play = pl;
}
