#include "Drawable.h"

Drawable::Drawable()
{
    //ctor
}

Drawable::~Drawable()
{
    //dtor
}


/////////////////
float* Drawable::getMesh() { return m_mesh; }
void Drawable::setMesh(float* m) { m_mesh = m; }

/////////////////////
dwe::vec3f Drawable::getPosition() { return m_node->getPosition(); }
void Drawable::setPosition(dwe::vec3f p) { m_node->setPosition(p); }

/////////////////////
dwe::vec3f Drawable::getRotation() { return m_node->getRotation(); }
void Drawable::setRotation(dwe::vec3f r) { m_node->setRotation(r); }

///////////////
void Drawable::setNode(dwe::Node* n) { m_node = n; }

///////////////
void Drawable::removeNode()
{
    m_node->remove();
    delete m_node;
    m_node = 0;
}
