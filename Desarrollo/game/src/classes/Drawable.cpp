#include "Drawable.h"

Drawable::Drawable()
{
    //ctor
    m_animation = dwe::eAnimNone;
}

Drawable::~Drawable()
{
    m_node->remove();
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
dwe::Node* Drawable::getNode() { return m_node; }

//////////////
void Drawable::setIAnimNode (scene::IAnimatedMeshSceneNode* n)
{
    ianim_node = n;
}

scene::IAnimatedMeshSceneNode* Drawable::getIAnimNode()
{
    return ianim_node;
}

///////////////
void Drawable::removeNode()
{
    m_node->remove();
    delete m_node;
    m_node = 0;
}

///////////////
void Drawable::setAnimation(dwe::AnimationType a)
{
    if(m_animation != a)
    {
        m_node->setAnimation(a);
        m_animation = a;
    }
}
dwe::AnimationType Drawable::getAnimation() { return m_animation; }
