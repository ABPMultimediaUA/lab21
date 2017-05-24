#include "ClippingObject.h"

ClippingObject::ClippingObject()
{
    //ctor
}

ClippingObject::~ClippingObject()
{
    //dtor
}

/////////////////////
void ClippingObject::setPosClipping(dwe::vec3f p)
{
    m_posClipping = p;
}

///////////////////////////
dwe::vec3f ClippingObject::getPosClipping()
{
    return m_posClipping;
}
