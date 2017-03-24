#ifndef FACHADEDIREENGINETEMPLATES_H
#define FACHADEDIREENGINETEMPLATES_H

#include "GraphicsEngine.h"

///////////////////////////////////////////////
// class Node
///////////////////////////////////////////////
template<class T>dwe::NodeTemplate<T>::NodeTemplate() {};
template<class T>dwe::NodeTemplate<T>::NodeTemplate(T* n)
{
    m_node = n;
}

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::setNode(T* n)
{
    m_node = n;
}

//////////////////////////////////////////
template<class T>T* dwe::NodeTemplate<T>::getNode()
{
    return m_node;
}

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::setColor(float r, float g, float b, float a)
{
    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
    m_color[3] = a;
}

//////////////////////////////////////////////
template<class T>float* dwe::NodeTemplate<T>::getColor()
{
    return m_color;
}

/*irr: template<class T>bool dwe::NodeTemplate<T>::intersects(scene::IAnimatedMeshSceneNode* n)
{
    return m_node->getTransformedBoundingBox().intersectsWithBox(n->getTransformedBoundingBox());
}

template<class T>void dwe::NodeTemplate<T>::setIAnimNode (scene::IAnimatedMeshSceneNode* n)
{
    ianim_node = n;
}*/

/*template<class T>scene::IAnimatedMeshSceneNode* dwe::NodeTemplate<T>::getIAnimNode()
{
    return ianim_node;
}*/

/***/

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::remove()
{
    if (m_node)
    {
        delete m_node;
        m_node = 0;
    }
}

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::move(vec3f v)
{
    GEInstance->getTagEngine()->moveNodeEntity(m_node, v);
    m_position.x += v.x;
    m_position.y += v.y;
    m_position.z += v.z;
}

//////////////////////////////////////////////////
template<class T>dwe::vec3f dwe::NodeTemplate<T>::getPosition()
{
    return m_position;
}

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::setPosition(vec3f v)
{
    GEInstance->getTagEngine()->setPositionNodeEntity(m_node, v);
    m_position = v;
}

//////////////////////////////////////////////////
template<class T>dwe::vec3f dwe::NodeTemplate<T>::getRotation()
{
    return m_rotation;
}

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::setRotation(dwe::vec3f v)
{
    GEInstance->getTagEngine()->setRotationNodeEntity(m_node, v);
    m_rotation = v;
}

//////////////////////////////////////////////////
template<class T>dwe::vec3f dwe::NodeTemplate<T>::getBoundingBox()
{
    // TODO: getBoundingBox
/*    if (m_node)
        return dwe::irrVector2dwe<float>(m_node->getTransformedBoundingBox().getExtent());
    else
        return dwe::vec3f(0,0,0);*/
    return dwe::vec3f(0,0,0);
}

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::setAnimation(AnimationType a)
{
    // TODO: setAnimation
    switch(a)
    {
    case eAnimStand:
        break;
    case eAnimRun:
        break;
    case eAnimWalk:
        break;
    case eAnimAttack:
        break;
    case eAnimNone:
        break;
    }
}

#endif // FACHADEDIREENGINETEMPLATES_H
