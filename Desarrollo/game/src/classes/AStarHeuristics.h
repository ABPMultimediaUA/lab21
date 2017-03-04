#ifndef ASTARHEURISTICS_H
#define ASTARHEURISTICS_H

#include "GraphicsEngine.h"

class Heuristic_Euclid
{
    public:

        Heuristic_Euclid(){}

        template <class graph_type>
        static float Calculate(const graph_type& G, int nd1, int nd2)
        {
            dwe::vec2f v1(G.GetNode(nd1).getPosition());
            dwe::vec2f v2(G.GetNode(nd2).getPosition());
            float ySeparation = v2.y - v1.y;
            float xSeparation = v2.x - v1.x;

            return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
        }
};

//-----------------------------------------------------------------------------
//manhattan distance
//-----------------------------------------------------------------------------
class Heuristic_Manhattan
{
    public:

        Heuristic_Manhattan(){}

        template <class graph_type>
        static double Calculate(const graph_type& G, int nd1, int nd2)
        {
            Vector2D v(G.GetNode(nd1).Pos() - G.GetNode(nd2).Pos());
            return abs(v.x + v.y);
        }
};

//-----------------------------------------------------------------------------
//this uses the euclidian distance but adds in an amount of noise to the
//result. You can use this heuristic to provide imperfect paths. This can
//be handy if you find that you frequently have lots of agents all following
//each other in single file to get from one place to another
//-----------------------------------------------------------------------------
class Heuristic_Noisy_Euclidian
{
    public:

        Heuristic_Noisy_Euclidian(){}

        //calculate the straight line distance from node nd1 to node nd2
        template <class graph_type>
        static double Calculate(const graph_type& G, int nd1, int nd2)
        {
            dwe::vec2f v1(G.GetNode(nd1).getPosition());
            dwe::vec2f v2(G.GetNode(nd2).getPosition());
            float ySeparation = v2.y - v1.y;
            float xSeparation = v2.x - v1.x;

            return sqrt(ySeparation*ySeparation + xSeparation*xSeparation) * rand()%(1.1f-0.9f+1)+0.9f;
        }
};

//-----------------------------------------------------------------------------
//you can use this class to turn the A* algorithm into Dijkstra's search.
//this is because Dijkstra's is equivalent to an A* search using a heuristic
//value that is always equal to zero.
//-----------------------------------------------------------------------------
class Heuristic_Dijkstra
{
    public:

        template <class graph_type>
        static double Calculate(const graph_type& G, int nd1, int nd2)
        {
            return 0;
        }
};

#endif // ASTARHEURISTICS_H
