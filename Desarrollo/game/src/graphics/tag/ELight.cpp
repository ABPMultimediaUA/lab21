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

tag::vec3f tag::ELight::getDiffuseIntensity() { return m_diffuseIntensity; }
void tag::ELight::setDiffuseIntensity( vec3f intensity ) { m_diffuseIntensity = intensity; }

tag::vec3f tag::ELight::getSpecularIntensity() { return m_specularIntensity; }
void tag::ELight::setSpecularIntensity( vec3f intensity ) { m_specularIntensity = intensity; }

tag::vec3f tag::ELight::getAmbientIntensity() { return m_ambientIntensity; }
void tag::ELight::setAmbientIntensity( vec3f intensity ) { m_ambientIntensity = intensity; }

bool tag::ELight::getIfLightOn() { return m_lightOn; }
void tag::ELight::setOnOff (bool on) { m_lightOn = on; }
