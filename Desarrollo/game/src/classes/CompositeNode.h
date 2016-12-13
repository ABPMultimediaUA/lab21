#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "Node.h"

class CompositeNode : public Node
{
    public:
        CompositeNode();
        virtual ~CompositeNode();
        void addChild (Node* child);


    protected:
        Node** children;
        int numChildren;

};

#endif // COMPOSITENODE_H
