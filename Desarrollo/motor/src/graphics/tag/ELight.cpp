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

glm::vec4 tag::ELight::getDiffuseIntensity() { return m_DiffuseIntensity; }
void tag::ELight::setDiffuseIntensity( glm::vec4 intensity ) { m_DiffuseIntensity = intensity; }

glm::vec4 tag::ELight::getSpecularIntensity() { return m_SpecularIntensity; }
void tag::ELight::setSpecularIntensity( glm::vec4 intensity ) { m_SpecularIntensity = intensity; }

glm::vec4 tag::ELight::getAmbientIntensity() { return m_AmbientIntensity; }
void tag::ELight::setAmbientIntensity( glm::vec4 intensity ) { m_AmbientIntensity = intensity; }

bool tag::ELight::getIfLightOn() { return m_lightOn; }
void tag::ELight::setOnOff (bool on) { m_lightOn = on; }
