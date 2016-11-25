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

class BaseDireWReplica;
class Player;
class PlayerMate;

namespace dwe
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
        Node();
        Node(ISceneNode* n);
        void move(vec3f v);
        vec3f getPosition();
        void setPosition(vec3f v);
        void setNode(ISceneNode* n);
    private:
        irr::scene::ISceneNode* m_node;
    };



    ///////////////////////////////////////////////
    // GraphicsEngine
    // ==============
    //
    ///////////////////////////////////////////////
    class GraphicsEngine
    {
    public:
        static GraphicsEngine* Instance();

        void init(AppReceiver* ar = 0);
        void release();
        void close();
        bool isRunning();
        void draw();
        Node* createNode(std::string meshName);
        bool isWindowActive();
        void yield();

        // Creacion de personajes
        Player* createMainPlayer();
        PlayerMate* createPlayerMate();

    private:
        irr::IrrlichtDevice*            m_device;
        irr::video::IVideoDriver*       m_driver;
        irr::scene::ISceneManager*      m_smgr;
        irr::gui::IGUIEnvironment*      m_guienv;

        GraphicsEngine() {};
    };
}

#define GEInstance dwe::GraphicsEngine::Instance()

#endif // FACHADEDIREENGINE_H
