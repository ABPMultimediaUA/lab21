#include "ScenaryElement.h"

ScenaryElement::ScenaryElement()
{
    // Parámetros de físicas por defecto
}

ScenaryElement::~ScenaryElement()
{
    //dtor
}

/////////////////////
void ScenaryElement::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f s = n->getBoundingBox();
    createStaticBody(getPosition(), s.x, s.z, getRotation().y);
}

/////////////////////
void ScenaryElement::update()
{
    // No necesita ya que es fijo
}

/////////////////////
void ScenaryElement::render()
{
    // TODO
}
