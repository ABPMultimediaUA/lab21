#include "ScenaryElement.h"

ScenaryElement::ScenaryElement()
{
    //ctor
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
    createStaticBox(getPosition(), s.x, s.z);
}

/////////////////////
void ScenaryElement::setPosition(dwe::vec3f p)
{
    setPosEntity(p, getRotation().y);
    Drawable::setPosition(p);
}

/////////////////////
void ScenaryElement::update()
{
    // No necesita ya que es fijo
    //Drawable::setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
}

/////////////////////
void ScenaryElement::render()
{
    // TODO
}
