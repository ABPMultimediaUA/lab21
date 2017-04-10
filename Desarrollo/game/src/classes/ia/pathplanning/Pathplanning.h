#ifndef PATHPLANNING_H
#define PATHPLANNING_H

#include "GraphicsEngine.h"

class Enemy;
class NavigationGraph;

class Pathplanning
{
    public:

        Pathplanning(Enemy *owner);

        virtual ~Pathplanning();

        void CreatePathToPosition(dwe::vec2f TargetPos);
        dwe::vec2f Movement();
        void CalculateDirection();
        //bool CheckIfRouteEnd();

    private:

        Enemy* m_owner;

        const NavigationGraph& m_NavGraph;

        dwe::vec2f nextPosition;
        dwe::vec2f finalPosition;
        dwe::vec2f direction;

        std::list<dwe::vec2f> route;

        int GetClosestNodeToPosition(dwe::vec2f pos);
        bool CheckIfArrived();
};

#endif
