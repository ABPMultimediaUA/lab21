#ifndef FACHADEDIREENGINE_H
#define FACHADEDIREENGINE_H

#include <irrlicht.h>
#include <string>
#include <AppReceiver.h>


using namespace std;

// Aun estando los namespace sigo definiendo las propiedades
// de los objetos con irr::core... para que c:b autocomplete bien
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace fde
{
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
    typedef vec3<float> vec3f;
    typedef vec3<int> vec3i;


    ///////////////////////////////////////////////
    // Node
    // ====
    //
    ///////////////////////////////////////////////
    class Node
    {
    public:
        Node(ISceneNode* n);
        void move(vec3f v);
    private:
        irr::scene::ISceneNode* m_node;
    };



    ///////////////////////////////////////////////
    // Graphics
    // ========
    //
    ///////////////////////////////////////////////
    class Graphics
    {
    public:
        void init(AppReceiver* ar = 0);
        void release();
        void close();
        bool isRunning();
        void draw();
        Node* createNode(std::string meshName);
        bool isWindowActive();
        void yield();

    private:
        irr::IrrlichtDevice*            m_device;
        irr::video::IVideoDriver*       m_driver;
        irr::scene::ISceneManager*      m_smgr;
        irr::gui::IGUIEnvironment*      m_guienv;
    };
}

#endif // FACHADEDIREENGINE_H
