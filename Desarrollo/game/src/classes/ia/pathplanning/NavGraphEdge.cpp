#include "NavGraphEdge.h"

NavGraphEdge::NavGraphEdge():from(-1), to(-1), cost(1.0)
{
    //ctor
}

NavGraphEdge::NavGraphEdge(int f, int t, float c):from(f), to(t), cost(c)
{
    //ctor
}

NavGraphEdge::~NavGraphEdge()
{
    //dtor
}

int NavGraphEdge::getFrom() const
{
    return from;
}
void NavGraphEdge::setFrom(int newIndex)
{
    from = newIndex;
}

int NavGraphEdge::getTo() const
{
    return to;
}

void NavGraphEdge::setTo(int newIndex)
{
    to = newIndex;
}

float NavGraphEdge::getCost() const
{
    return cost;
}

void NavGraphEdge::setCost(float newCost)
{
    cost = newCost;
}
