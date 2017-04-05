#include "AStarAlgorithm.h"
#include "AStarHeuristics.h"
#include "NavGraphEdge.h"
#include "PriorityQueue.h"

Graph_SearchAStar::Graph_SearchAStar(const NavigationGraph &graph, int source, int target):
                                     m_Graph(graph),
                                     m_GCosts(graph.getNumNodes(), 0.0),
                                     m_FCosts(graph.getNumNodes(), 0.0),
                                     m_ShortestPathTree(graph.getNumNodes()),
                                     m_SearchFrontier(graph.getNumNodes()),
                                     m_iSource(source),
                                     m_iTarget(target)
{
    Search();
}

std::vector<const NavGraphEdge*> Graph_SearchAStar::GetSPT()const
{
    return m_ShortestPathTree;
}

float Graph_SearchAStar::GetCostToTarget()const
{
    return m_GCosts[m_iTarget];
}

void Graph_SearchAStar::Search()
{
    //create an indexed priority queue of nodes. The nodes with the
    //lowest overall F cost (G+H) are positioned at the front.
    IndexedPriorityQLow<float> pq(m_FCosts, m_Graph.getNumNodes());

    //put the source node on the queue
    pq.insert(m_iSource);

    //while the queue is not empty
    while(!pq.empty())
    {
        //get lowest cost node from the queue
        int NextClosestNode = pq.Pop();
        //move this node from the frontier to the spanning tree
        m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];

        //if the target has been found exit
        if (NextClosestNode == m_iTarget) return;

        //now to test all the edges attached to this node
        typename NavigationGraph::EdgeIterator EdgeItr(m_Graph, NextClosestNode);

        for (const NavGraphEdge* pE=EdgeItr.begin();
        !EdgeItr.end();
        pE=EdgeItr.next())
        {
            //calculate the heuristic cost from this node to the target (H)
            float HCost = Heuristic_Euclid::Calculate(m_Graph, m_iTarget, pE->getTo());

            //calculate the 'real' cost to this node from the source (G)
            float GCost = m_GCosts[NextClosestNode] + pE->getCost();

            //if the node has not been added to the frontier, add it and update
            //the G and F costs
            if (m_SearchFrontier[pE->getTo()] == 0)
            {
                m_FCosts[pE->getTo()] = GCost + HCost;
                m_GCosts[pE->getTo()] = GCost;

                pq.insert(pE->getTo());

                m_SearchFrontier[pE->getTo()] = pE;
            }

            //if this node is already on the frontier but the cost to get here
            //is cheaper than has been found previously, update the node
            //costs and frontier accordingly.
            else if ((GCost < m_GCosts[pE->getTo()]) && (m_ShortestPathTree[pE->getTo()]==0))
            {
                m_FCosts[pE->getTo()] = GCost + HCost;
                m_GCosts[pE->getTo()] = GCost;

                pq.ChangePriority(pE->getTo());

                m_SearchFrontier[pE->getTo()] = pE;
            }
        }
    }
}

//-----------------------------------------------------------------------------
std::list<dwe::vec2f> Graph_SearchAStar::GetPathToTarget()const
{
    std::list<dwe::vec2f> path;

    //just return an empty path if no target or no path found
    if (m_iTarget < 0)  return path;

    int nd = m_iTarget;

    if(m_ShortestPathTree[nd] != 0)
        path.push_front(m_Graph.getNode(nd).getPosition());

    while ((nd != m_iSource) && (m_ShortestPathTree[nd] != 0))
    {
        nd = m_ShortestPathTree[nd]->getFrom();
        path.push_front(m_Graph.getNode(nd).getPosition());
    }

    return path;
}
