#include "tag/GraphicNode.h"

#include "tag/Entity.h"

#include <algorithm>


tag::GraphicNode::GraphicNode() :
    m_entity(0),
    m_childs(),
    m_parent(0)
{
    //ctor
}

tag::GraphicNode::~GraphicNode()
{
    //dtor
    // TODO en el destructor deberíamos borrar todos los hijos (delete)
}

////////////////////////////////////
tag::GraphicNode* tag::GraphicNode::getParent() const { return m_parent; }
void tag::GraphicNode::setParent(tag::GraphicNode* parent) { m_parent = parent; }


///////////////////////
bool tag::GraphicNode::setEntity(tag::Entity* e){ m_entity = e; return true; };
tag::Entity* tag::GraphicNode::getEntity() const { return m_entity; }

///////////////////////////////
unsigned int tag::GraphicNode::addChild(tag::GraphicNode* n)
{
    m_childs.push_back(n);
    n->setParent(this);
    return (m_childs.size() - 1);  // devolvemos el indice añadido
}

///////////////////////////////
unsigned int tag::GraphicNode::removeChild(const tag::GraphicNode* n)
{
    m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), n), m_childs.end());
    return (m_childs.size()); // Devolvemos cantidad de hijos
}

///////////////////////
void tag::GraphicNode::draw()
{
    if (m_entity != 0)
        m_entity->beginDraw();

    for(std::vector<GraphicNode*>::iterator it = m_childs.begin(); it != m_childs.end(); it++)
        (*it)->draw();

    if (m_entity != 0)
        m_entity->endDraw();
}
