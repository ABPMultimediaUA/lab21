#include "Pathplanning.h"
#include "Humanoid.h"

#include "AStarAlgorithm.h"
#include "AStarHeuristics.h"

#include "Scene.h"

#include "WorldInstance.h"

#include "dwVectors.h"

#include <limits>

Pathplanning::Pathplanning(Enemy *owner):m_NavGraph(Scene::Instance()->getNavGraph())
{
    m_owner = owner;

    direction = dwe::vec2f(0,0);
    finalPosition = dwe::vec2f(0,0);
}

Pathplanning::~Pathplanning()
{
}

void Pathplanning::SetNext(dwe::vec2f next)
{
    nextPosition = next;
}

int Pathplanning::GetClosestNodeToPosition(dwe::vec2f targetPos)
{
    int closestNode = -1;
    float shortestDistance = std::numeric_limits<float>::max();
    float distance;

    typename NavigationGraph::NodeIterator NodeItr(m_NavGraph);

    for (const NavGraphNode* pN=NodeItr.begin(); !NodeItr.end(); pN=NodeItr.next())
    {
        distance = dwu::calculateSquaredDistance(targetPos, dwe::vec2f(pN->getPosition()));
        if(distance < shortestDistance){
            shortestDistance = distance;
            closestNode = pN->getIndex();
        }
    }
    return closestNode;
}

void Pathplanning::CreatePathToPosition(dwe::vec2f TargetPos)
{
    dwe::vec2f positionb((m_owner->getPosEntity().x)*0.035, (m_owner->getPosition().z)*0.035);
    dwe::vec2f targetposition(TargetPos.x*0.035, TargetPos.y*0.035);
    if(!(positionb.x == targetposition.x && positionb.y == targetposition.y) && !World->CheckWallsRayCast(positionb, targetposition)) //Si puede ir directo no calcula el camino
    {
        route.clear();
        nextPosition = TargetPos;
        finalPosition = TargetPos;

    }
    else    //Si hay obstaculos en medio calcula el camino
    {
        dwe::vec2f position((m_owner->getPosEntity().x), (m_owner->getPosition().z));
        int target(GetClosestNodeToPosition(TargetPos));
        int source(GetClosestNodeToPosition(position));

        if(target < 0 || source < 0)
            return;

        nextPosition = TargetPos;

        Graph_SearchAStar a(m_NavGraph, source, target);
        route = a.GetPathToTarget();

        if(route.size()>0){
            nextPosition = route.front();
            route.pop_front();
            route.push_back(TargetPos);
            finalPosition = TargetPos;
        }
    }
    //if(route.size())
        //PathSmooth();
    CalculateDirection();
}

void Pathplanning::PathSmooth()
{
    dwe::vec2f route2[route.size()];
    int pos = 0;
    std::list<dwe::vec2f>::const_iterator iterator;
    for(iterator = route.begin(); iterator != route.end(); ++iterator)
    {
        std::cout<<"ITERATOR X "<<(*iterator).x << " ITERATOR Y " << (*iterator).y<<std::endl;
        route2[pos] = *iterator;
        ++pos;
    }
    std::list<dwe::vec2f> newRoute;
    dwe::vec2f position(m_owner->getPosition().x, m_owner->getPosition().z);
    int num = -1;
    bool entro = false;
    while(num<pos)
    {
        for(int i = pos; i > num; i--)
        {
            dwe::vec2f positionb(position.x*0.035, position.y*0.035);
            dwe::vec2f positionb2(route2[i].x*0.035, route2[i].y*0.035);
            if(!(positionb.x == positionb2.x && positionb.y == positionb2.y) && !World->CheckWallsRayCast(position, positionb2))
            {
                std::cout<<"I :"<<i<<std::endl;
                position = route2[i];
                num = i;
                newRoute.push_back(position);
                i=0;
                entro = true;
            }
        }
        if(!entro)
        {
            ++num;
            position = route2[num];
        }
        entro = false;
    }

    if(route.size())
        route = newRoute;
    for(iterator = route.begin(); iterator != route.end(); ++iterator)
        std::cout<<"NEWROUTE X "<<(*iterator).x << " NEWROUTE Y " << (*iterator).y<<std::endl;
    nextPosition = route.front();
    route.pop_front();
}

void Pathplanning::CalculateDirection()
{
    dwe::vec3f currentPosition(m_owner->getPosition());

    dwe::vec2f dir(nextPosition.x - currentPosition.x, nextPosition.y - currentPosition.z);

    direction = dwu::normalizeVector(dir);

}

dwe::vec2f Pathplanning::Movement()
{
    if(CheckIfArrived()){
        if(route.size()){
            nextPosition = route.front();
            route.pop_front();
            CalculateDirection();
        }
        else{
            direction.x = direction.y = 0;
        }
    }
    CalculateDirection();

    return direction;

}

void Pathplanning::Clear()
{
    route.clear();
    dwe::vec3f position = m_owner->getPosition();
    nextPosition.x = position.x;
    nextPosition.y = position.z;
}

bool Pathplanning::CheckIfRouteEnd()
{
    if(CheckIfArrived())
        return !route.size();
    return false;
}

bool Pathplanning::CheckIfArrived()
{
    dwe::vec3f position = m_owner->getPosition();
    return ( abs(position.x - nextPosition.x) < m_owner->getSpeed() && abs(position.z - nextPosition.y) < m_owner->getSpeed() );
}
