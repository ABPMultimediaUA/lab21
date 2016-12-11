#include "CompositeNode.h"

CompositeNode::CompositeNode()
{
    //ctor
}

CompositeNode::~CompositeNode()
{
    //dtor
}

void CompositeNode::addChild (Node* child)
{
    children[numChildren] = child;
    numChildren++;
}
