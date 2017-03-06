#include "AStarAlgorithm.h"
#include "PriorityQueue.h"

template <class graph_type, class heuristic>
Graph_SearchAStar<graph_type, heuristic>::Graph_SearchAStar(graph_type &graph, int source, int target):
                                                            m_Graph(graph),
                                                            m_ShortestPathTree(graph.NumNodes()),
                                                            m_SearchFrontier(graph.NumNodes()),
                                                            m_GCosts(graph.NumNodes(), 0.0),
                                                            m_FCosts(graph.NumNodes(), 0.0),
                                                            m_iSource(source),
                                                            m_iTarget(target)
{
    Search();
}

template <class graph_type, class heuristic>
std::vector<typename graph_type::edge_type*> Graph_SearchAStar<graph_type, heuristic>::GetSPT()const
{
    return m_ShortestPathTree;
}

template <class graph_type, class heuristic>
float Graph_SearchAStar<graph_type, heuristic>::GetCostToTarget()const
{
    return m_GCosts[m_iTarget];
}

template <class graph_type, class heuristic>
void Graph_SearchAStar<graph_type, heuristic>::Search()
{
    //create an indexed priority queue of nodes. The nodes with the
    //lowest overall F cost (G+H) are positioned at the front.
    IndexedPriorityQLow<float> pq(m_FCosts, m_Graph.NumNodes());

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
        typename graph_type::EdgeIterator EdgeItr(m_Graph, NextClosestNode);

        for (typename graph_type::edge_type* pE=EdgeItr.begin();
        !EdgeItr.end();
        pE=EdgeItr.next())
        {
            //calculate the heuristic cost from this node to the target (H)
            float HCost = heuristic::Calculate(m_Graph, m_iTarget, pE->To());

            //calculate the 'real' cost to this node from the source (G)
            float GCost = m_GCosts[NextClosestNode] + pE->Cost();

            //if the node has not been added to the frontier, add it and update
            //the G and F costs
            if (m_SearchFrontier[pE->To()] == 0)
            {
                m_FCosts[pE->To()] = GCost + HCost;
                m_GCosts[pE->To()] = GCost;

                pq.insert(pE->To());

                m_SearchFrontier[pE->To()] = pE;
            }

            //if this node is already on the frontier but the cost to get here
            //is cheaper than has been found previously, update the node
            //costs and frontier accordingly.
            else if ((GCost < m_GCosts[pE->To()]) && (m_ShortestPathTree[pE->To()]==0))
            {
                m_FCosts[pE->To()] = GCost + HCost;
                m_GCosts[pE->To()] = GCost;

                pq.ChangePriority(pE->To());

                m_SearchFrontier[pE->To()] = pE;
            }
        }
    }
}

//-----------------------------------------------------------------------------
template <class graph_type, class heuristic>
std::list<int> Graph_SearchAStar<graph_type, heuristic>::GetPathToTarget()const
{
    std::list<int> path;

    //just return an empty path if no target or no path found
    if (m_iTarget < 0)  return path;

    int nd = m_iTarget;

    path.push_front(nd);

    while ((nd != m_iSource) && (m_ShortestPathTree[nd] != 0))
    {
        nd = m_ShortestPathTree[nd]->From();
        path.push_front(nd);
    }

    return path;
}
