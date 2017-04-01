#include "Pathplanning.h"
#include "Humanoid.h"

#include "AStarAlgorithm.h"
#include "AStarHeuristics.h"

#include "Scene.h"

#include <limits>

Pathplanning::Pathplanning(Enemy *owner):m_NavGraph(Scene::Instance()->getNavGraph())
{
    m_owner = owner;

    //m_NavGraph = Scene::Instance()->getNavGraph();

    direction = dwe::vec2f(0,0);

    finalPosition = dwe::vec2f(0,0);
    nextPosition = dwe::vec2f(0,0);

    //currentNode = nextNode = finalNode = 0;
}

Pathplanning::~Pathplanning()
{
}

dwe::vec2f Pathplanning::GetClosestNodeToPosition(dwe::vec2f targetPos)
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
    dwe::vec2f target(GetClosestNodeToPosition(TargetPos));
    dwe::vec2f source(GetClosestNodeToPosition(dwe::vec2f(m_owner->getPosition().x, m_owner->getPosition().z)));

    Graph_SearchAStar a(m_NavGraph, source, target);
    route = a.GetPathToTarget();
    if(route.size()>0){
        nextNode = route.front();
        route.pop_front();
        finalNode = route.back();
        CalculateDirection(dwe::vec2f(m_owner->getPosition().x, m_owner->getPosition().z));
    }
}

void Pathplanning::CalculateDirection(dwe::vec2f v1)
{
    dwe::vec2f v2(m_NavGraph.getNode(nextNode).getPosition());

    dwe::vec2f vec(v2.x - v1.x, v2.y - v1.y);

    Normalize(vec);

    direction = vec;
}

dwe::vec2f Pathplanning::Movement()
{
    if(CheckIfArrived()){
        currentNode = nextNode;
        if(!CheckIfRouteEnd()){
            nextNode = route.front();
            route.pop_front();
            CalculateDirection(m_NavGraph.getNode(currentNode).getPosition());
        }
        else{
            direction.x = direction.y = 0;
            if(!CheckIfTargetReached())
                CalculateDirection(finalPosition);
        }
    }
    return direction;

}

bool Pathplanning::CheckIfTargetReached()
{
    dwe::vec3f position = m_owner->getPosition();
    return ( abs(position.x - finalPosition.x) < m_owner->getSpeed() && abs(position.z - finalPosition.y) < m_owner->getSpeed() );
}

bool Pathplanning::CheckIfRouteEnd()
{
    return (currentNode == finalNode);
}

bool Pathplanning::CheckIfArrived()
{
    dwe::vec3f position = m_owner->getPosition();
    return ( abs(position.x - m_NavGraph.getNode(nextNode).getPosition().x) < m_owner->getSpeed() && abs(position.z - m_NavGraph.getNode(nextNode).getPosition().y) < m_owner->getSpeed() );
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
