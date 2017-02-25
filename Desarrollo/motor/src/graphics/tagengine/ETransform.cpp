#include "ETransform.h"

dwe::ETransform::ETransform()
{
    //ctor
}

dwe::ETransform::~ETransform()
{
    //dtor
}

//////////////////////
void dwe::ETransform::identity()
{
    m_matrix = glm::mat4();

}

/////////////////
void dwe::ETransform::load(glm::mat4 m)
{
    m_matrix = m;

}

/////////////////
glm::mat4 dwe::ETransform::getMatrix()
{
    return m_matrix;
}

/////////////////
void dwe::ETransform::traspose()
{
    m_matrix = glm::transpose(m_matrix);
}

/////////////////
void dwe::ETransform::translate(vec3f t)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(t.x, t.y, t.z));
}

/////////////////
void dwe::ETransform::translate(float x, float y, float z)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(x, y, z));
}


/////////////////
void dwe::ETransform::rotate(vec3f t)
{
    dwe::ETransform::rotate(t.x, t.y, t.z);
}

/////////////////
void dwe::ETransform::rotate(float x, float y, float z)
{
    float toRad = M_PI / 180;

    if (x != 0)
    {
        x = x * toRad;
        m_matrix = glm::rotate(m_matrix, x, glm::vec3(1, 0, 0));
    }


    if (y != 0)
    {
        y = y * toRad;
        m_matrix = glm::rotate(m_matrix, y, glm::vec3(0, 1, 0));
    }


    if (z != 0)
    {
        z = z * toRad;
        m_matrix = glm::rotate(m_matrix, z, glm::vec3(0, 0, 1));
    }


}

/////////////////
void dwe::ETransform::scale(vec3f s)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(s.x, s.y, s.z));
}

/////////////////
void dwe::ETransform::scale(float x, float y, float z)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(x, y, z));
}

std::stack<glm::mat4> dwe::EntitiesAttributes::m_stack;
glm::mat4 dwe::EntitiesAttributes::m_ModelViewMatrix;
/////////////////
void dwe::ETransform::beginDraw()
{
    std::cout << "Begin " << m_cadena << "\n";
    //std::cout << "estoy en " << glm::to_string(m_matrix) << endl;

    dwe::EntitiesAttributes::m_stack.push(dwe::EntitiesAttributes::m_ModelViewMatrix);
    dwe::EntitiesAttributes::m_ModelViewMatrix *= m_matrix;

    cout << "Begin, modelmatrix : " << glm::to_string(dwe::EntitiesAttributes::m_ModelViewMatrix) << endl;
}

/////////////////
void dwe::ETransform::endDraw()
{
    std::cout << "End " << m_cadena << "\n";

    dwe::EntitiesAttributes::m_stack.pop();

    dwe::EntitiesAttributes::m_ModelViewMatrix = m_matrix;

    cout << "End, modelmatrix : " << glm::to_string(dwe::EntitiesAttributes::m_ModelViewMatrix) << endl;
}



