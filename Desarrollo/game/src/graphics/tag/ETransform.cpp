#include "tag/ETransform.h"

#define GLEW_STATIC
#include<GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>


tag::ETransform::ETransform() :
    m_matrix(1.0f)
{
}

tag::ETransform::~ETransform()
{
    //dtor
}

//////////////////////
void tag::ETransform::identity()
{
    m_matrix = glm::mat4(1.0f);
}

//////////////////////
void tag::ETransform::load(glm::mat4 m)
{
    m_matrix = m;
}

///////////////////////////
glm::mat4 tag::ETransform::getMatrix()
{
    return m_matrix;
}

//////////////////////
void tag::ETransform::transpose()
{
    m_matrix = glm::transpose(m_matrix);
}

//////////////////////
void tag::ETransform::translate(vec3f t)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(t.x, t.y, t.z));
}

//////////////////////
void tag::ETransform::translate(float x, float y, float z)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(x, y, z));
}


//////////////////////
void tag::ETransform::rotate(vec3f t)
{
    rotate(t.x, t.y, t.z);
}

//////////////////////
void tag::ETransform::rotate(float x, float y, float z)
{
    if (x) m_matrix = glm::rotate(m_matrix, (float)glm::radians(x), glm::vec3(1, 0, 0));
    if (y) m_matrix = glm::rotate(m_matrix, (float)glm::radians(y), glm::vec3(0, 1, 0));
    if (z) m_matrix = glm::rotate(m_matrix, (float)glm::radians(z), glm::vec3(0, 0, 1));
}

//////////////////////
void tag::ETransform::scale(vec3f s)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(s.x, s.y, s.z));
}

//////////////////////
void tag::ETransform::scale(float x, float y, float z)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(x, y, z));
}


//////////////////////
void tag::ETransform::beginDraw()
{
    Entity::TStack.push(Entity::modelMatrix);
    Entity::modelMatrix = m_matrix * Entity::modelMatrix;
}

//////////////////////
void tag::ETransform::endDraw()
{
    Entity::modelMatrix = Entity::TStack.top();
    Entity::TStack.pop();
}



