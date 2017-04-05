#ifndef NAVIGATIONGRAPH_H
#define NAVIGATIONGRAPH_H

#include <vector>
#include <list>

class NavGraphNode;
class NavGraphEdge;

class NavigationGraph
{
    public:

        NavigationGraph(bool di);

        NavGraphNode& getNode(int idx);
        const NavGraphNode& getNode(int idx)const;
        NavGraphEdge& getEdge(int from, int to);
        const NavGraphEdge& getEdge(int from, int to)const;
        int getNextFreeNodeIndex()const;
        int addNode(NavGraphNode node);
        void removeNode(int node);
        void addEdge(NavGraphEdge edge);
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

        typedef std::vector<NavGraphNode>   NodeVector;
        typedef std::list<NavGraphEdge>     EdgeList;
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

                typename EdgeList::const_iterator         curEdge;
                const NavigationGraph&  G;
                const int                           NodeIndex;

            public:

                EdgeIterator(const NavigationGraph& graph, int node);
                const NavGraphEdge*  begin();
                const NavGraphEdge*  next();
                bool end();
        };

    friend class EdgeIterator;

    class NodeIterator
    {
        private:

            typename NodeVector::const_iterator			curNode;
            const NavigationGraph& G;
            void GetNextValidNode(typename NodeVector::const_iterator& it);

        public:

            NodeIterator(const NavigationGraph &graph);
            const NavGraphNode* begin();
            const NavGraphNode* next();
            bool end();
    };

    friend class ConstNodeIterator;
};

#endif // NAVIGATIONGRAPH_H
