#include "NavGraphNode.h"

NavGraphNode::NavGraphNode()
{
    //ctor
}

NavGraphNode::NavGraphNode(int idx, dwe::vec3f pos) : index(idx), position(pos)
{

}

NavGraphNode::~NavGraphNode()
{
    //dtor
}

void NavGraphNode::setIndex(int idx)
{
    index = idx;
}

void NavGraphNode::setPosition(dwe::vec2f pos)
{
    position = pos;
}

int NavGraphNode::getIndex()
{
    return index;
}

dwe::vec2f NavGraphNode::getPosition()
{
    return position;
}
