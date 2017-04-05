#ifndef ASTARALGORITHM_H
#define ASTARALGORITHM_H

#include <vector>
#include <list>
#include "GraphicsEngine.h"

class NavigationGraph;
class NavGraphEdge;

class Graph_SearchAStar
{
    private:

        const NavigationGraph& m_Graph;

        //indexed into my node. Contains the 'real' accumulative cost to that node
        std::vector<float> m_GCosts;

        //indexed into by node. Contains the cost from adding m_GCosts[n] to
        //the heuristic cost from n to the target node. This is the vector the
        //iPQ indexes into.
        std::vector<float> m_FCosts;

        std::vector<const NavGraphEdge*> m_ShortestPathTree;
        std::vector<const NavGraphEdge*> m_SearchFrontier;

        int m_iSource;
        int m_iTarget;

        //the A* search algorithm
        void Search();

    public:

        Graph_SearchAStar(const NavigationGraph &graph, int source, int target);

        //returns the vector of edges that the algorithm has examined
        std::vector<const NavGraphEdge*> GetSPT()const;

        //returns a vector of node indexes that comprise the shortest path
        //from the source to the target
        std::list<dwe::vec2f> GetPathToTarget()const;

        //returns the total cost to the target
        float GetCostToTarget()const;
};

#endif // ASTARALGORITHM_H
