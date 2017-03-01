#include "GraphEdge.h"

GraphEdge::GraphEdge():from(-1), to(-1), cost(1.0)
{
    //ctor
}

GraphEdge::GraphEdge(int f, int t, float c):from(f), to(t), cost(c)
{
    //ctor
}

GraphEdge::~GraphEdge()
{
    //dtor
}

int GraphEdge::getFrom() const
{
    return from;
}
void GraphEdge::setFrom(int newIndex)
{
    from = newIndex;
}

int GraphEdge::getTo() const
{
    return to;
}

void GraphEdge::setTo(int newIndex)
{
    to = newIndex;
}

float GraphEdge::getCost() const
{
    return cost;
}

void GraphEdge::setCost(float newCost)
{
    cost = newCost;
}
