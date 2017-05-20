#include "tag/GraphicNode.h"

#include "tag/Entity.h"
#include "tag/EMesh.h"
#include "tag/EAnimation.h"

#include <algorithm>


tag::GraphicNode::GraphicNode() :
    m_entity(0),
    m_childs(),
    m_parent(0),
    m_active(true)
{
    //ctor
}

tag::GraphicNode::~GraphicNode()
{
    // Borramos los hijos
    //   borramos punteros
    for(std::vector<GraphicNode*>::iterator it = m_childs.begin(); it != m_childs.end(); it++)
        delete (*it);
    //   vaciamos vector hijos
    m_childs.clear();
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
void tag::GraphicNode::drawChilds()
{
    for(std::vector<GraphicNode*>::iterator it = m_childs.begin(); it != m_childs.end(); it++)
        (*it)->draw();
}

///////////////////////
void tag::GraphicNode::draw()
{
    if (m_active)
    {
        if (m_entity)
        {
            m_entity->beginDraw();
            drawChilds();
            m_entity->endDraw();
        }
        else
            drawChilds();
    }
}

///////////////////////
bool tag::GraphicNode::isEmptyNode() const
{
    return (!m_entity && !m_childs.size());
}

/////////////////////////////
tag::vec3f tag::GraphicNode::getBoundingBox()
{
    EMesh* mesh;
    EAnimation* anim;
    if (m_entity && (mesh = dynamic_cast<EMesh*>(m_entity)))
        return mesh->getBoundingBox();
    else if (m_entity && (anim = dynamic_cast<EAnimation*>(m_entity)))
        return anim->getBoundingBox();
    else
        return vec3f(0,0,0);
}

/////////////////////////////
tag::EAnimation* tag::GraphicNode::getAnimation()
{
    EAnimation* anim;
    if (m_entity && (anim = dynamic_cast<EAnimation*>(m_entity)))
        return anim;
    return 0;
}

///////////////////////
bool tag::GraphicNode::setActive(bool active)
{
    m_active = active;
}





