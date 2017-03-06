#include "NavGraphNode.h"

NavGraphNode::NavGraphNode():GraphNode(-1)
{
    //ctor
}

NavGraphNode::NavGraphNode(int idx, dwe::vec2f pos) : GraphNode(idx), position(pos)
{

}

NavGraphNode::~NavGraphNode()
{
    //dtor
}

void NavGraphNode::setPosition(dwe::vec2f pos)
{
    position = pos;
}

dwe::vec2f NavGraphNode::getPosition()const
{
    return position;
}
