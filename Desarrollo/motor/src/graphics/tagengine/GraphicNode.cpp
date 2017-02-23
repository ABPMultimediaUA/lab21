#include "GraphicNode.h"

#include "Entity.h"

#include <algorithm>


dwe::GraphicNode::GraphicNode()
{
    //ctor
}

dwe::GraphicNode::~GraphicNode()
{
    //dtor
}

////////////////////////////////////
dwe::GraphicNode* dwe::GraphicNode::getParent() { return m_parent; }


///////////////////////
bool dwe::GraphicNode::setEntity(dwe::Entity* e){ m_entity = e; return true; };
dwe::Entity* dwe::GraphicNode::getEntity() { return m_entity; }

///////////////////////////////
unsigned int dwe::GraphicNode::addChild(dwe::GraphicNode* n)
{
    m_childs.push_back(n);
    return (m_childs.size() - 1);  // devolvemos el indice añadido
}

///////////////////////////////
unsigned int dwe::GraphicNode::removeChild(const dwe::GraphicNode* n)
{
    m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), n), m_childs.end());
    return (m_childs.size()); // Devolvemos cantidad de hijos
}

///////////////////////
void dwe::GraphicNode::draw()
{
    if (m_entity != 0)
        m_entity->beginDraw();

    for(std::vector<GraphicNode*>::iterator it = m_childs.begin(); it != m_childs.end(); it++)
        (*it)->draw();

    if (m_entity != 0)
        m_entity->endDraw();
}
