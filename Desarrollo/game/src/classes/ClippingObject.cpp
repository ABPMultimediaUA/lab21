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
void ClippingObject::setParamsClipping(ClippingVec4f p)
{
    m_paramsClipping = p;
}

//////////////////////////////
ClippingVec4f ClippingObject::getParamsClipping()
{
    return m_paramsClipping;
}
