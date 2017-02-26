#ifndef TAGTYPES_H
#define TAGTYPES_H

namespace tag
{
    ///////////////////////////////////////////////
    // vec2
    // ====
    //
    ///////////////////////////////////////////////
    template <class T>
    class vec2
    {
    public:
        T x;
        T y;

        // Constructor con xyz a cero
        vec2() : x(0), y(0) {};
        // Constructor con el mismo valor para xyz
        vec2(T _p) : x(_p), y(_p) {};
        // Constructor con valores xyz
        vec2(T _x, T _y) : x(_x), y(_y) {};
        // Constructor con los valores de otro vec2
        vec2(const vec2<T>& v) : x(v.x), y(v.y) {};
    };
    typedef vec2<glm::f32> vec2f;
    typedef vec2<int> vec2i;


    ///////////////////////////////////////////////
    // vec3
    // ====
    //
    ///////////////////////////////////////////////
    template <class T>
    class vec3
    {
    public:
        T x;
        T y;
        T z;

        // Constructor con xyz a cero
        vec3() : x(0), y(0), z(0) {};
        // Constructor con el mismo valor para xyz
        vec3(T _p) : x(_p), y(_p), z(_p) {};
        // Constructor con valores xyz
        vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
        // Constructor con los valores de otro vec3
        vec3(const vec3<T>& v) : x(v.x), y(v.y), z(v.z) {};
    };
    typedef vec3<glm::f32> vec3f;
    typedef vec3<int> vec3i;
}

#endif // TAGTYPES_H
