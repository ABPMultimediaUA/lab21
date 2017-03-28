#ifndef NAVGRAPHNODE_H
#define NAVGRAPHNODE_H

#include "GraphicsEngine.h"

class NavGraphNode
{
    public:

        NavGraphNode();
        NavGraphNode(int idx, dwe::vec2f);

        virtual ~NavGraphNode();

        int getIndex()const;
        void setIndex(int newIndex);
        dwe::vec2f getPosition() const;
        void setPosition(dwe::vec2f pos);

    protected:

        int index;
        dwe::vec2f position;

    private:
};

#endif // NAVGRAPHNODE_H
