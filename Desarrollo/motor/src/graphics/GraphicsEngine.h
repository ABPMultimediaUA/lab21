#ifndef FACHADEDIREENGINE_H
#define FACHADEDIREENGINE_H

#define GLEW_STATIC

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <list>
#include <AppReceiver.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Nombre de los attributes
#define A_POSITION  "a_Position"
#define A_NORMAL    "a_Normal"

// Nombre de los uniforms
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_VMATRIX               "u_VMatrix"
#define U_COLOR                 "u_Color"
#define U_LUZ0                  "u_Luz0"




#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define MAX_MESSAGE_LINES 4




using namespace std;

class AppReceiver;
class Player;
class Program;

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

    /*template<typename T> vec3<T> irrVector2dwe(irr::core::vector3d<T> irrV)
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
    }*/

    ///////////////////////////////////////////////
    // Arbol de escena
    ///////////////////////////////////////////////
    class Entity
    {
        public:
            Entity() {};
            ~Entity() {};

            std::string m_cadena;

            virtual void beginDraw() = 0;
            virtual void endDraw() = 0;
    };

    class ETransform : public Entity
    {
        public:
            ETransform() {};
            ~ETransform() {};

            void identity();
            void load(glm::mat4 m);
            void traspose();

            void translate(vec3f t);
            void translate(float x, float y, float z);

            void rotate(vec3f r);
            void rotate(float x, float y, float z);

            void beginDraw();
            void endDraw();

        private:
            glm::mat4   m_matrix;
    };

    class ELight : public Entity
    {
        public:
            ELight() {};
            ~ELight() {};

            void beginDraw();
            void endDraw();
    };

    class ECamera : public Entity
    {
        public:
            ECamera() {};
            ~ECamera() {};

            void beginDraw();
            void endDraw();
    };

    class EMesh : public Entity
    {
        public:
            EMesh() {};
            ~EMesh() {};

            void beginDraw();
            void endDraw();
    };

    class GraphicNode
    {
        public:
            GraphicNode() {};
            ~GraphicNode() {};

            unsigned int addChild(GraphicNode* n);
            //unsigned int removeChild(GraphicNode* n);

            bool setEntity(Entity* e);
            Entity* getEntity();
            GraphicNode* getParent();

            void draw();

        private:
            Entity*                 m_entity;
            vector<GraphicNode*>    m_childs;
            GraphicNode*            m_parent;

    };


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

            void setColor(float r, float g, float b, float a);
            float* getColor();

            void setNode(T* n);
            /**T* getNode();**/
            void remove();

            vec3f getBoundingBox();

            void setAnimation(AnimationType a);

            vec3f getTransformedBoundingBox();
            void setTransformedBoundingBox(vec3f v);

            //irr: bool intersects(scene::IAnimatedMeshSceneNode* n);
            T* getNode();

            /***/ // TODO: ¿se puede quitar? No se puede poner algo así en la fachada
            //irr: void setIAnimNode (scene::IAnimatedMeshSceneNode* n);
            //irr: scene::IAnimatedMeshSceneNode* getIAnimNode();
            /**/
        private:
            T*          m_node;
            vec3f       m_position;
            vec3f       m_rotation;
            float       m_color[4];
            //irr: scene::IAnimatedMeshSceneNode* ianim_node;  /**/ // TODO: ¿se puede quitar? No se puede poner algo así en la fachada
    };

    typedef NodeTemplate<const aiScene> Node;
    //irr: typedef NodeTemplate<ISceneNode> Node;
    //irr: typedef NodeTemplate<IAnimatedMeshSceneNode> Node;

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

        void init();
        void release();
        void close();
        bool isRunning();
        void draw();
        Node* createNode(std::string meshName);
        bool isWindowActive();
        void yield();


        //////////////////////////
        // Creacion de elementos
        Player* createMainPlayer();


        //////////////////////////////
        // Eventos de teclado y ratón
        AppReceiver receiver;

        void updateCamera(const vec3f playerPosition);

        /// \brief Muestra un mensaje en la zona de mensajes
        /// \details Añade un mensaje a los mensajes que ya hay pasando los demás a lineas superiores y añadiendo
        /// el texto pasado a la línea más baja. Si se supera el número máximo de mensajes el de la fila superior
        /// se borrar. No admite acentos.
        /// \param[in] text Texto a mostrar en la lista de mensajes
        void addMessageLine(std::string text);


        /// \brief Devuelve la posición X Y del puntero del ratón
        /// \return vec2f con las coordenadas x y
        vec2f getMousePosition();


    private:
        sf::RenderWindow*   m_window;
        sf::Clock           m_clock;
        float               m_secondsLastDraw;
        Program*            m_shaderProgram;
        std::list<Node*>    m_scenes;
        Assimp::Importer    m_importer;   // OJO tiene que estar aqui, si es local da errores de memoria segmentation fault

        sf::Font            m_font;
        sf::Text            m_messageLine[MAX_MESSAGE_LINES];


        // Handles de los attributes y uniforms
        int m_aPositionLocation;
        int m_aNormalLocation;
        int m_uProjectionMatrixLocation;
        int m_uMVMatrixLocation;
		int m_uVMatrixLocation;
		int m_uColorLocation;
		int m_uLuz0Location;

		glm::mat4 m_projectionMatrix; // Almacena la matriz de proyección
        glm::mat4 m_viewMatrix;       // Almacena la matriz de la vista (cámara)

        GLfloat m_view_position[3];
        GLfloat m_view_rotate[16];
        float m_scale;


        //scene::IAnimatedMeshSceneNode* createIrrAnimatedMeshSceneNode(std::string meshName);

        // Camara
        float tarUD;
        float tarLR;
        static const unsigned short _camera_desviation  = 50;
        static const float          _camera_progression = 0.5f;
        static const int            _camera_y           = 250;
        static const int            _camera_z_offset    = -100;

        GraphicsEngine() {};

        void render();
    };
}

#define GEInstance dwe::GraphicsEngine::Instance()

#endif // FACHADEDIREENGINE_H
