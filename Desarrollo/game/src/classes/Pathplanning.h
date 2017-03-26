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

        void CreatePathToPosition(int target);

        dwe::vec2f Movement();

        bool CheckIfRouteEnd();

        float CalculateAngleYAxis(dwe::vec2f vec);

    private:

        Enemy* m_owner;

        const NavigationGraph& m_NavGraph;

        int currentNode;

        int nextNode;

        int finalNode;

        dwe::vec2f direction;

        std::list<int> route;

        //int GetClosestNodeToPosition(dwe::vec2f pos)const;

        void CalculateDirection();
        bool CheckIfArrived();
        void Normalize(dwe::vec2f& vec);
};

#endif
