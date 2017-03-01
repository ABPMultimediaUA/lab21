#ifndef SPARSEGRAPH_C
#define SPARSEGRAPH_C

#include "SparseGraph.h"

template <class node_type, class edge_type>
SparseGraph<node_type, edge_type>::SparseGraph(bool di):nextNodeIndex(0), digraph(di), numActiveNodes(0)
{
}

template <class node_type, class edge_type>
node_type& SparseGraph<node_type, edge_type>::getNode(int idx)const
{
    if(idx < nodes.size() && idx >=0)
        return nodes[idx];
}

template <class node_type, class edge_type>
edge_type& SparseGraph<node_type, edge_type>::getEdge(int from, int to)const
{
    if(from < nodes.size() && from >=0 && nodes[from].getIndex() != -1)
    if(to < nodes.size() && to >=0 && nodes[to].getIndex() != -1)

    for (typename EdgeList::iterator curEdge = edges[from].begin();
         curEdge != edges[from].end();
         ++curEdge)
    {
        if (curEdge->getTo() == to) return *curEdge;
    }
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::getNextFreeNodeIndex()const
{
    return nextNodeIndex;
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::addNode(node_type node)
{
    if (node.getIndex() < nodes.size())
    {
        if(nodes[node.getIndex()].getIndex() == -1)
            nodes[node.getIndex()] = node;
        return nextNodeIndex;
    }
    if(node.getIndex() == nextNodeIndex)
    {
        nodes.push_back(node);
        edges.push_back(EdgeList());
        return ++nextNodeIndex;
    }
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::RemoveInvalidEdges()
{
    for (typename EdgeListVector::iterator curEdgeList = edges.begin(); curEdgeList != edges.end(); ++curEdgeList)
    {
        for (typename EdgeList::iterator curEdge = (*curEdgeList).begin(); curEdge != (*curEdgeList).end(); ++curEdge)
        {
            if (nodes[curEdge->getTo()].getIndex() == -1 ||
                nodes[curEdge->getFrom()].getIndex() == -1)
            {
                curEdge = (*curEdgeList).erase(curEdge);
            }
        }
    }
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::removeNode(int node)
{
    if(node < nodes.size())
    {
        nodes[node].setIndex(-1);

        if (!digraph)
        {
            for (typename EdgeList::iterator curEdge = edges[node].begin();
                 curEdge != edges[node].end();
                 ++curEdge)
            {
                for (typename EdgeList::iterator curE = edges[curEdge->getTo()].begin();
                     curE != edges[curEdge->getTo()].end();
                     ++curE)
                {
                    if (curE->getTo() == node)
                    {
                        curE = edges[curEdge->getTo()].erase(curE);
                        break;
                    }
                }
            }
            edges[node].clear();
        }
        else
        {
            RemoveInvalidEdges();
        }
    }
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::addEdge(edge_type edge)
{
    if(edge.getFrom() < nextNodeIndex && edge.getTo() < nextNodeIndex)
    {
        if (nodes[edge.getTo()].getIndex() != -1 &&
            nodes[edge.getFrom()].getIndex() != -1)
        {
            if (UniqueEdge(edge.getFrom(), edge.getTo()))
            {
                edges[edge.getFrom()].push_back(edge);
            }
            if (!digraph)
            {
                if (UniqueEdge(edge.getTo(), edge.getFrom()))
                {
                    edge_type newEdge(edge.getTo(), edge.getFrom(), edge.getCost());
                    edges[edge.getTo()].push_back(newEdge);
                }
            }
        }
    }
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::removeEdge(int from, int to)
{
    if(from < nodes.size() && to < nodes.size())
    {
        typename EdgeList::iterator curEdge;
        if (!digraph)
        {
            for (curEdge = edges[to].begin();
                 curEdge != edges[to].end();
                 ++curEdge)
            {
                if (curEdge->getTo() == from)
                {
                    curEdge = edges[to].erase(curEdge);
                    break;
                }
            }
        }
        for (curEdge = edges[from].begin();
             curEdge != edges[from].end();
             ++curEdge)
        {
            if (curEdge->getTo() == to)
            {
                curEdge = edges[from].erase(curEdge);
                break;
            }
        }
    }
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::UniqueEdge(int from, int to)
{
    for (typename EdgeList::iterator curEdge = edges[from].begin();
         curEdge != edges[from].end();
         ++curEdge)
    {
        if (curEdge->getTo() == to)
            return false;
    }
    return true;
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::setEdgeCost(int from, int to, float newCost)
{
    if(from < nodes.size() && to < nodes.size())
    {
        for (typename EdgeList::iterator curEdge = edges[from].begin();
             curEdge != edges[from].end();
             ++curEdge)
        {
            if (curEdge->getTo() == to)
            {
                curEdge->setCost(newCost);
                break;
            }
        }
    }
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::getNumNodes()const
{
    return nodes.size();
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::getNumActiveNodes()const
{
    return numActiveNodes;
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::getNumEdges()const
{
    int count = 0;
    for (int e=0; e<edges.size(); ++e)
        count += edges[e].size();
    return count;
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isDigraph()const
{
    return digraph;
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isEmpty()const
{
    return nodes.empty();
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isNodePresent(int node)const
{
    if (node >= nodes.size() || node < 0 || nodes[node].getIndex() == -1)
        return false;
    return true;
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isEdgePresent(int from, int to)const
{
    if (isNodePresent(from) && isNodePresent(from))
    {
        for (typename EdgeList::iterator curEdge = edges[from].begin();
             curEdge != edges[from].end();
             ++curEdge)
        {
            if (curEdge->getTo() == to) return true;
        }
    }
    return false;
}

#endif // SPARSEGRAPH_C
