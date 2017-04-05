#include "NavGraphNode.h"

NavGraphNode::NavGraphNode():index(-1)
{
    //ctor
}

NavGraphNode::NavGraphNode(int idx, dwe::vec2f pos) : index(idx), position(pos)
{

}

NavGraphNode::~NavGraphNode()
{
    //dtor
}

void NavGraphNode::setIndex(int newIndex)
{
    index = newIndex;
}

int NavGraphNode::getIndex() const
{
    return index;
}

void NavGraphNode::setPosition(dwe::vec2f pos)
{
    position = pos;
}

dwe::vec2f NavGraphNode::getPosition()const
{
    return position;
}
