#include "dwVectors.h"
#include "GraphicsEngine.h"

/////////////////////////
dwe::vec2f dwu::normalizeVector(const dwe::vec2f v)
{
    dwe::vec2f normalizedV(0,0);
    if(v.x || v.y)
    {
        float magnitud = sqrt(pow(v.x,2) + pow(v.y,2));
        normalizedV.x = v.x / magnitud;
        normalizedV.y = v.y / magnitud;
    }
    return normalizedV;
}

//////////////////////
float dwu::calculateDegrees(const dwe::vec2f normalizedVector1, const dwe::vec2f normalizedVector2)
{
    return acos(normalizedVector1.x*normalizedVector2.x + (normalizedVector1.y*normalizedVector2.y)) * (180/M_PI);
}
