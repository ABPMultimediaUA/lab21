#ifndef ASTARHEURISTICS_H
#define ASTARHEURISTICS_H

#include "NavigationGraph.h"
#include "NavGraphNode.h"

class Heuristic_Euclid
{
    public:

        Heuristic_Euclid(){}

        static float Calculate(const NavigationGraph& G, int nd1, int nd2)
        {
            dwe::vec2f v1(G.getNode(nd1).getPosition());
            dwe::vec2f v2(G.getNode(nd2).getPosition());
            float ySeparation = v2.y - v1.y;
            float xSeparation = v2.x - v1.x;

            return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
        }
};

#endif // ASTARHEURISTICS_H
