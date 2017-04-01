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

        bool CheckIfRouteEnd();

        float CalculateAngleYAxis(dwe::vec2f vec);

    private:

        Enemy* m_owner;

        const NavigationGraph& m_NavGraph;

        dwe::vec2f nextPosition;

        dwe::vec2f finalPosition;

        dwe::vec2f direction;

        std::list<dwe::vec2f> route;

        int GetClosestNodeToPosition(dwe::vec2f pos);

        float CalculateQuadraticDistance(dwe::vec2f targetPos, dwe::vec2f nodePos)const;


        void CalculateDirection(dwe::vec2f source);
        bool CheckIfArrived();
        bool CheckIfTargetReached();
        void Normalize(dwe::vec2f& vec);
};

#endif
