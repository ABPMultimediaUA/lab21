#include "Drawable.h"

Drawable::Drawable()
{
    //ctor
    m_animation = dwe::eAnimNone;
}

Drawable::~Drawable()
{
    if (m_node)
    {
        m_node->remove();
        m_node = 0;
    }
}

/////////////////////
dwe::vec3f Drawable::getPosition() { return m_node->getPosition(); }
void Drawable::setPosition(dwe::vec3f p) { m_node->setPosition(p); }

/////////////////////
dwe::vec3f Drawable::getRotation() { return m_node->getRotation(); }
void Drawable::setRotation(dwe::vec3f r) { m_node->setRotation(r); }

///////////////
void Drawable::setNode(dwe::Node* n) { m_node = n; }
dwe::Node* Drawable::getNode() { return m_node; }
bool Drawable::hasNode() { return (m_node != 0); }


///////////////
void Drawable::removeNode()
{
    if (m_node)
    {
        m_node->remove();
        delete m_node;
        m_node = 0;
    }
}

///////////////
void Drawable::setAnimation(dwe::AnimationType a)
{
    if(m_node && m_animation != a)
    {
        m_node->setAnimation(a);
        m_animation = a;
    }
}
dwe::AnimationType Drawable::getAnimation() { return m_animation; }

///////////////
void Drawable::setActive(bool active)
{
    if (m_node)
        m_node->setActive(active);
}

dwe::vec3f Drawable::getBoundingBox()
{
    if (m_node)
        return m_node->getBoundingBox();
    else
    {
        std::cerr << "Drawable getBoundingBox sin m_node\n";
        return dwe::vec3f(0,0,0);
    }
}
