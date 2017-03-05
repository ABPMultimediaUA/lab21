#include "tag/ECamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

tag::ECamera::ECamera()
{
    //ctor
    m_isPerspective = true;
}

tag::ECamera::~ECamera()
{
    //dtor
}

void tag::ECamera::beginDraw() {};
void tag::ECamera::endDraw() {};

bool tag::ECamera::getIfPerspective() { return m_isPerspective; }
bool tag::ECamera::getIfActive() { return m_isActive; }

void tag::ECamera::setActive(bool active) { m_isActive = active; }

void tag::ECamera::setPerspective(float fov, float aspect, float near, float far)
{
    m_isPerspective = true;

    m_projectionMatrix = glm::perspective(fov, aspect, near, far);
}

void tag::ECamera::setParallel(float fov, float aspect, float near, float far)
{
    m_isPerspective = false;

    //////
}

glm::mat4 tag::ECamera::getProjectionMatrix() { return m_projectionMatrix; }
