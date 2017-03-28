#include "NavigationGraph.h"
#include "NavGraphEdge.h"
#include "NavGraphNode.h"

NavigationGraph::NavigationGraph(bool di):nextNodeIndex(0), digraph(di), numActiveNodes(0)
{
}

NavGraphNode& NavigationGraph::getNode(int idx)
{
    if(idx < nodes.size() && idx >=0)
        return nodes[idx];
}

const NavGraphNode& NavigationGraph::getNode(int idx)const
{
    if(idx < nodes.size() && idx >=0)
        return nodes[idx];
}

NavGraphEdge& NavigationGraph::getEdge(int from, int to)
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

const NavGraphEdge& NavigationGraph::getEdge(int from, int to)const
{
    if(from < nodes.size() && from >=0 && nodes[from].getIndex() != -1)
    if(to < nodes.size() && to >=0 && nodes[to].getIndex() != -1)

    for (typename EdgeList::const_iterator curEdge = edges[from].begin();
         curEdge != edges[from].end();
         ++curEdge)
    {
        if (curEdge->getTo() == to) return *curEdge;
    }
}

int NavigationGraph::getNextFreeNodeIndex()const
{
    return nextNodeIndex;
}

int NavigationGraph::addNode(NavGraphNode node)
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

void NavigationGraph::RemoveInvalidEdges()
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

void NavigationGraph::removeNode(int node)
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

void NavigationGraph::addEdge(NavGraphEdge edge)
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
                    NavGraphEdge newEdge(edge.getTo(), edge.getFrom(), edge.getCost());
                    edges[edge.getTo()].push_back(newEdge);
                }
            }
        }
    }
}

void NavigationGraph::removeEdge(int from, int to)
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

bool NavigationGraph::UniqueEdge(int from, int to)
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

void NavigationGraph::setEdgeCost(int from, int to, float newCost)
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

int NavigationGraph::getNumNodes()const
{
    return nodes.size();
}

int NavigationGraph::getNumActiveNodes()const
{
    return numActiveNodes;
}

int NavigationGraph::getNumEdges()const
{
    int count = 0;
    for (int e=0; e<edges.size(); ++e)
        count += edges[e].size();
    return count;
}

bool NavigationGraph::isDigraph()const
{
    return digraph;
}

bool NavigationGraph::isEmpty()const
{
    return nodes.empty();
}

bool NavigationGraph::isNodePresent(int node)const
{
    if (node >= nodes.size() || node < 0 || nodes[node].getIndex() == -1)
        return false;
    return true;
}

bool NavigationGraph::isEdgePresent(int from, int to)const
{
    if (isNodePresent(from) && isNodePresent(from))
    {
        for (typename EdgeList::const_iterator curEdge = edges[from].begin();
             curEdge != edges[from].end();
             ++curEdge)
        {
            if (curEdge->getTo() == to) return true;
        }
    }
    return false;
}

/*****************************************************ITERATORS***************************************************/

NavigationGraph::EdgeIterator::EdgeIterator(const NavigationGraph& graph, int node): G(graph), NodeIndex(node)
{
    curEdge = G.edges[NodeIndex].begin();
}

const NavGraphEdge* NavigationGraph::EdgeIterator::begin()
{
    curEdge = G.edges[NodeIndex].begin();
    return &(*curEdge);
}

const NavGraphEdge* NavigationGraph::EdgeIterator::next()
{
    ++curEdge;
    if (end()) return 0;
        return &(*curEdge);
}

bool NavigationGraph::EdgeIterator::end()
{
    return (curEdge == G.edges[NodeIndex].end());
}
