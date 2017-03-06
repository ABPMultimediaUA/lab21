#include "GraphNode.h"

GraphNode::GraphNode():index(-1)
{
    //ctor
}

GraphNode::GraphNode(int idx):index(idx)
{

}

GraphNode::~GraphNode()
{
    //dtor
}

int GraphNode::getIndex() const
{
    return index;
}

void GraphNode::setIndex(int newIndex)
{
    index = newIndex;
}
