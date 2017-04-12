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

////////////////////////////////////////////
template<class T>bool dwe::NodeTemplate<T>::intersects(Node* n)
{
    if (m_node)
    {
        vec3f boundingBox = m_node->getBoundingBox();

        // Como el eje está en el centro, calculo la posicion +- la mitad del bounding
        boundingBox.x /= 2.0f;
        boundingBox.y /= 2.0f;
        boundingBox.z /= 2.0f;

        vec3f nodeMins(m_position.x - boundingBox.x,
                       m_position.y - boundingBox.y,
                       m_position.z - boundingBox.z);

        vec3f nodeMaxs(m_position.x + boundingBox.x,
                       m_position.y + boundingBox.y,
                       m_position.z + boundingBox.z);

        if (n)
        {
            boundingBox = n->getBoundingBox();
            boundingBox.x /= 2.0f;
            boundingBox.y /= 2.0f;
            boundingBox.z /= 2.0f;

            vec3f posn = n->getPosition();

            vec3f nMins(posn.x - boundingBox.x,
                        posn.y - boundingBox.y,
                        posn.z - boundingBox.z);

            vec3f nMaxs(posn.x + boundingBox.x,
                        posn.y + boundingBox.y,
                        posn.z + boundingBox.z);

            // Comprobamos interseccion
            return (   (nodeMaxs.x > nMins.x && nodeMins.x < nMaxs.x)   // Intersecta en X
                    && (nodeMaxs.y > nMins.y && nodeMins.y < nMaxs.y)   // Intersecta en Y
                    && (nodeMaxs.z > nMins.z && nodeMins.z < nMaxs.z) );// Intersecta en Z
        }
        else
            return false;
    }
    else
        return false;
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

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::remove()
{
    if (m_node)
    {
        GEInstance->getTagEngine()->deleteNode(m_node);
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
    if (m_node)
        return m_node->getBoundingBox();
    else
        return vec3f(0,0,0);
}

////////////////////////////////////////////
template<class T>void dwe::NodeTemplate<T>::setAnimation(AnimationType a)
{
    GEInstance->getTagEngine()->setAnimation(m_node, a);
}

#endif // FACHADEDIREENGINETEMPLATES_H
