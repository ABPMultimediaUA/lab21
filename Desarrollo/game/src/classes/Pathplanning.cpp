#include "Pathplanning.h"
#include "Humanoid.h"

#include "AStarAlgorithm.h"
#include "AStarHeuristics.h"

#include "Scene.h"

#include <limits>

Pathplanning::Pathplanning(Enemy *owner):m_NavGraph(Scene::Instance()->getNavGraph())
{
    m_owner = owner;

    direction = dwe::vec2f(0,0);
    finalPosition = dwe::vec2f(0,0);
    nextPosition = dwe::vec2f(0,0);
}

Pathplanning::~Pathplanning()
{
}

int Pathplanning::GetClosestNodeToPosition(dwe::vec2f targetPos)
{
    int closestNode = -1;
    float shortestDistance = std::numeric_limits<float>::max();
    float distance;

    typename NavigationGraph::NodeIterator NodeItr(m_NavGraph);

    for (const NavGraphNode* pN=NodeItr.begin(); !NodeItr.end(); pN=NodeItr.next())
    {
        distance = CalculateQuadraticDistance(targetPos, dwe::vec2f(pN->getPosition()));
        if(distance < shortestDistance){
            shortestDistance = distance;
            closestNode = pN->getIndex();
        }
    }
    return closestNode;
}

float Pathplanning::CalculateQuadraticDistance(dwe::vec2f targetPos, dwe::vec2f nodePos) const
{
    float x = targetPos.x - nodePos.x;
    float y = targetPos.y - nodePos.y;

    return x*x + y*y;
}

void Pathplanning::CreatePathToPosition(dwe::vec2f TargetPos)
{
    int target(GetClosestNodeToPosition(TargetPos));
    int source(GetClosestNodeToPosition(dwe::vec2f(m_owner->getPosition().x, m_owner->getPosition().z)));

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
    CalculateDirection();
}

void Pathplanning::CalculateDirection()
{
    dwe::vec3f currentPosition(m_owner->getPosition());

    dwe::vec2f dir(nextPosition.x - currentPosition.x, nextPosition.y - currentPosition.z);

    Normalize(dir);

    direction = dir;
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

    return direction;

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

void Pathplanning::Normalize(dwe::vec2f& vec)
{
    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
    vec.x /= length;
    vec.y /= length;
}

float Pathplanning::CalculateAngleYAxis(dwe::vec2f vec)
{
    float angle = (float)  (    acos(       ((double)1*vec.x + (double)0*vec.y)     )* 180/M_PI     );
    if(vec.y>0)
        angle = -angle;
    return angle;
}
