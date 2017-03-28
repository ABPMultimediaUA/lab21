#include "PathplanningTask.h"
#include "Pathplanning.h"

PathplanningTask::PathplanningTask(Pathplanning* p, Enemy* owner)
{
    m_pathplanning = p;
    m_owner = owner;
    brunning = false;
    time = 3000;
}

PathplanningTask::~PathplanningTask()
{
    //dtor
}

States PathplanningTask::run()
{
    if(m_pathplanning->CheckIfRouteEnd()){
        m_pathplanning->CreatePathToPosition(rand()%8);
    }
    return success;
}
