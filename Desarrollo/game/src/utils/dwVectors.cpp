#include "dwVectors.h"
#include "GraphicsEngine.h"
#define M_PI		3.14159265358979323846
/////////////////////////
dwe::vec2f dwu::normalizeVector(const dwe::vec2f v)
{
    dwe::vec2f normalizedV(0,0);
    if(v.x || v.y)
    {
        float magnitud = sqrt(v.x*v.x + v.y*v.y);
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

float dwu::calculateSquaredDistance(const dwe::vec2f position1, const dwe::vec2f position2)
{
    float x = position1.x - position2.x;
    float y = position1.y - position2.y;

    return x*x + y*y;
}

float dwu::calculateDistance(const dwe::vec2f position1, const dwe::vec2f position2)
{
    float x = position1.x - position2.x;
    float y = position1.y - position2.y;

    return sqrt(x*x + y*y);
}

float dwu::calculateAngleYAxis(const dwe::vec2f normalizedVector)
{
    dwe::vec2f yAxis(1,0);
    float angle = calculateDegrees(normalizedVector, yAxis);
    if(normalizedVector.y>0)
        angle = -angle;
    return angle;
}
