#include "tag/ECamera.h"

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

void tag::ECamera::setPerspective(float fov, float aspect, float near, float far)
{
    m_isPerspective = true;

    /////
}

void tag::ECamera::setParallel(float fov, float aspect, float near, float far)
{
    m_isPerspective = false;

    //////
}
