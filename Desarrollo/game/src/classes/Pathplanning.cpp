#include "Pathplanning.h"
#include "Humanoid.h"

#include "AStarAlgorithm.h"
#include "AStarHeuristics.h"

#include "Scene.h"

Pathplanning::Pathplanning(Enemy *owner):m_NavGraph(Scene::Instance()->getNavGraph())
{
    m_owner = owner;

    //m_NavGraph = Scene::Instance()->getNavGraph();

    direction = dwe::vec2f(0,0);

    currentNode = nextNode = finalNode = 0;
}

Pathplanning::~Pathplanning()
{
}

void Pathplanning::CreatePathToPosition(int target)
{
    //int target = GetClosestNodeToPosition(TargetPos);
    //int source = GetClosestNodeToPosition(dwe::vec2f(m_owner->getPosition().x, m_owner->getPosition().z));
    int source = currentNode;
    //int target = 4;
    Graph_SearchAStar a(m_NavGraph, source, target);
    route = a.GetPathToTarget();
    if(route.size()>0){
        nextNode = route.front();
        route.pop_front();
        finalNode = route.back();
        CalculateDirection();
    }
}

void Pathplanning::CalculateDirection()
{
    dwe::vec2f v1(m_NavGraph.getNode(currentNode).getPosition());
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
            CalculateDirection();
        }
        else
            direction.x = direction.y = 0;
    }
    return direction;

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
