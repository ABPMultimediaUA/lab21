#ifndef NAVGRAPHNODE_H
#define NAVGRAPHNODE_H

#include "GraphNode.h"
#include "GraphicsEngine.h"

class NavGraphNode : public GraphNode
{
    public:

        NavGraphNode();
        NavGraphNode(int idx, dwe::vec2f);

        virtual ~NavGraphNode();

        dwe::vec2f getPosition() const;
        void setPosition(dwe::vec2f pos);

    protected:

        dwe::vec2f position;

    private:
};

#endif // NAVGRAPHNODE_H
