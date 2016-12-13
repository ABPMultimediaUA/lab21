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
class Humanoid;
class Dog;
class Door;

namespace dwe
{

    ///////////////////////////////////////////////
    // AnimationType
    // =============
    //
    ///////////////////////////////////////////////
    enum AnimationType {
        eAnimNone,
        eAnimStand,
        eAnimWalk,
        eAnimRun,
        eAnimAttack
    };



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
    typedef vec3<f32> vec3f;
    typedef vec3<int> vec3i;

    template<typename T> vec3<T> irrVector2dwe(irr::core::vector3d<T> irrV)
    {
        vec3<T> v;
        v.x = irrV.X;
        v.y = irrV.Y;
        v.z = irrV.Z;
        return v;
    }

    template<typename T> irr::core::vector3d<T> dweVector2irr(vec3<T> dweV)
    {
        irr::core::vector3df v;
        v.X = dweV.x;
        v.Y = dweV.y;
        v.Z = dweV.z;
        return v;
    }


    ///////////////////////////////////////////////
    // Node
    // ====
    //
    ///////////////////////////////////////////////
    template <class T>
    class NodeTemplate
    {
    public:
        NodeTemplate();
        NodeTemplate(T* n);
        void move(vec3f v);

        vec3f getPosition();
        void setPosition(vec3f v);

        vec3f getRotation();
        void setRotation(vec3f v);

        void setNode(T* n);
        void remove();

        void setAnimation(AnimationType a);

    private:
        T* m_node;
    };

    //typedef NodeTemplate<ISceneNode> Node;
    typedef NodeTemplate<IAnimatedMeshSceneNode> Node;

    #include "GraphicsEngineTemplates.cpp"  // La implementación de templates se tiene que incluir siempre en el h




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
        Humanoid* createEnemyHumanoid();
        Dog* createEnemyDog();
        Door* createDoor();

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
