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

template<class T>void dwe::NodeTemplate<T>::setNode(T* n)
{
    m_node = n;
}

/***
template<class T>T* dwe::NodeTemplate<T>::getNode()
{
    return m_node;
}***/

/***/
template<class T>void dwe::NodeTemplate<T>::setIAnimNode (scene::IAnimatedMeshSceneNode* n)
{
    ianim_node = n;
}

template<class T>scene::IAnimatedMeshSceneNode* dwe::NodeTemplate<T>::getIAnimNode()
{
    return ianim_node;
}

/***/

////////////////
template<class T>void dwe::NodeTemplate<T>::remove()
{
    m_node->remove();
}

template<class T>void dwe::NodeTemplate<T>::move(vec3f v)
{
    irr::core::vector3df _v = m_node->getPosition();
    _v.X += v.x;
    _v.Y += v.y;
    _v.Z += v.z;
    m_node->setPosition(_v);
}

template<class T>dwe::vec3f dwe::NodeTemplate<T>::getPosition()
{
    // Se obtiene la posición de Irrlicht del nodo y se pasa a vector de dwe
    return dwe::irrVector2dwe<float>(m_node->getPosition());
}

template<class T>void dwe::NodeTemplate<T>::setPosition(vec3f v)
{
    // El vector pasado como vec3f se pasa al vector de tipo irrlicht
    m_node->setPosition(dwe::dweVector2irr<float>(v));
}

template<class T>dwe::vec3f dwe::NodeTemplate<T>::getRotation()
{
    return dwe::irrVector2dwe<float>(m_node->getRotation());
}

template<class T>void dwe::NodeTemplate<T>::setRotation(dwe::vec3f v)
{
    m_node->setRotation(dwe::dweVector2irr<float>(v));
}


template<class T>void dwe::NodeTemplate<T>::setAnimation(AnimationType a)
{
    switch(a)
    {
    case eAnimStand:
        m_node->setMD2Animation(scene::EMAT_STAND);
        break;
    case eAnimRun:
        m_node->setMD2Animation(scene::EMAT_RUN);
        break;
    case eAnimWalk:
        m_node->setMD2Animation(scene::EMAT_CROUCH_WALK);
        break;
    case eAnimAttack:
        m_node->setMD2Animation(scene::EMAT_ATTACK);
        break;
    }
}

#endif // FACHADEDIREENGINETEMPLATES_H
