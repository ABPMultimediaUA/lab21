#include "tag/ELight.h"

tag::ELight::ELight()
{
    //ctor
}

tag::ELight::~ELight()
{
    //dtor
}

void tag::ELight::beginDraw() {};
void tag::ELight::endDraw() {};

GLfloat tag::ELight::getIntensity() { return m_intensity; }
void tag::ELight::setIntensity( GLfloat intensity ) { m_intensity = intensity; }
