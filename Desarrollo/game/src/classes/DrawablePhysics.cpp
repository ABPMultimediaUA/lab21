#include "DrawablePhysics.h"

DrawablePhysics::DrawablePhysics()
{
    //ctor
}

DrawablePhysics::~DrawablePhysics()
{
    //dtor
}

//////////////////////
void DrawablePhysics::setPosition(dwe::vec3f p)
{
    EntityPhysics::setPosEntity(p, getRotation().y);
    Drawable::setPosition(p);
}

