#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

//#include "NavGraphNode.h"

#include <vector>
#include <list>

template <class node_type, class edge_type>
class SparseGraph
{
    public:

        SparseGraph(bool di);

        node_type& getNode(int idx)const;
        edge_type& getEdge(int from, int to)const;
        int getNextFreeNodeIndex()const;
        int addNode(node_type node);
        void removeNode(int node);
        void addEdge(edge_type edge);
        void removeEdge(int from, int to);
        void setEdgeCost(int from, int to, float newCost);
        void RemoveInvalidEdges();
        bool UniqueEdge(int from, int to);

        int getNumNodes()const;
        int getNumActiveNodes()const;
        int getNumEdges()const;
        bool isDigraph()const;
        bool isEmpty()const;
        bool isNodePresent(int node)const;
        bool isEdgePresent(int from, int to)const;

    protected:

    private:

        typedef std::vector<node_type>   NodeVector;
        typedef std::list<edge_type>     EdgeList;
        typedef std::vector<EdgeList>    EdgeListVector;

        NodeVector nodes;
        EdgeListVector edges;

        bool digraph;

        int nextNodeIndex;

        int numActiveNodes;

    public:

        class EdgeIterator
        {
            private:

                typename EdgeList::iterator         curEdge;
                SparseGraph<node_type, edge_type>&  G;
                const int                           NodeIndex;

            public:

                EdgeIterator(SparseGraph<node_type, edge_type>& graph, int node);
                edge_type*  begin();
                edge_type*  next();
                bool end();
        };

    friend class EdgeIterator;
};

#include "SparseGraph.cpp"

#endif // SPARSEGRAPH_H
