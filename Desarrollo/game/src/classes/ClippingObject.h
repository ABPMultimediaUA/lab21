#ifndef CLIPPINGOBJECT_H
#define CLIPPINGOBJECT_H

#include "Drawable.h"

template <class T>
class ClippingVec4
{
public:
    T x;
    T y;
    T sizeX;
    T sizeY;

    // Constructor con xyz a cero
    ClippingVec4() : x(0), y(0), sizeX(0), sizeY(0) {};
    // Constructor con el mismo valor para xyz
    ClippingVec4(T _p) : x(_p), y(_p), sizeX(_p), sizeY(_p) {};
    // Constructor con valores xyz
    ClippingVec4(T _x, T _y, T _sizeX, T _sizeY) : x(_x), y(_y), sizeX(_sizeX), sizeY(_sizeY) {};
    // Constructor con los valores de otro ClippingVec4
    ClippingVec4(const ClippingVec4<T>& v) : x(v.x), y(v.y), sizeX(v.sizeX), sizeY(v.sizeY) {};
    // Operador =
    ClippingVec4& operator= (const ClippingVec4<T>& v){x = v.x; y = v.y; sizeX = v.sizeX; sizeY = v.sizeY; return *this;};

};
typedef ClippingVec4<glm::f32> ClippingVec4f;

class ClippingObject : public Drawable
{
    public:
        ClippingObject();
        ~ClippingObject();   // No para heredar

        virtual void update() {};
        virtual void render() {};

        void setParamsClipping(ClippingVec4f p);
        ClippingVec4f getParamsClipping();

    protected:

    private:
        dwe::vec3f getPosition() { return dwe::vec3f(0); };
        void setPosition(dwe::vec3f p) {};

        void setAnimation(dwe::AnimationType a);
        dwe::AnimationType getAnimation();

        ClippingVec4f m_paramsClipping;
};

#endif // CLIPPINGOBJECT_H
