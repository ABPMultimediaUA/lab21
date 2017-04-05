#include "PathplanningTask.h"
#include "Pathplanning.h"
#include "WorldInstance.h"
#include "Player.h"

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

    if(m_pathplanning->CheckIfRouteEnd() || time>500){
        dwe::vec3f pos(World->getMainPlayer()->getPosition());
        m_pathplanning->CreatePathToPosition(dwe::vec2f(pos.x, pos.z));
        time=0;
    }
    time++;
    return success;
}
