#ifndef FACHADEDIREENGINE_H
#define FACHADEDIREENGINE_H

#define GLEW_STATIC
#include<GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <string>
#include <list>
#include <AppReceiver.h>


#define MAX_MESSAGE_LINES 4

#include "tag/ResourceMesh.h"
#include "tag/TAGEngine.h"
#include "tag/GraphicNode.h"




using namespace std;

class AppReceiver;
class Player;
class Program;
class Gun;

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
    typedef tag::vec2f vec2f;


    ///////////////////////////////////////////////
    // vec3
    // ====
    //
    ///////////////////////////////////////////////
    typedef tag::vec3f vec3f;


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

    typedef NodeTemplate<tag::GraphicNode> Node;
    //irr: typedef NodeTemplate<ISceneNode> Node;
    //irr: typedef NodeTemplate<IAnimatedMeshSceneNode> Node;





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
        Player* createMainPlayer(Gun* gun);


        //////////////////////////////
        // Eventos de teclado y ratón
        AppReceiver receiver;

        void createCamera();
        void updateCamera(const dwe::vec3f playerPosition, int moreEnemiesX, int moreEnemiesZ);

        /// \brief Muestra un mensaje en la zona de mensajes
        /// \details Añade un mensaje a los mensajes que ya hay pasando los demás a lineas superiores y añadiendo
        /// el texto pasado a la línea más baja. Si se supera el número máximo de mensajes el de la fila superior
        /// se borrar. No admite acentos.
        /// \param[in] text Texto a mostrar en la lista de mensajes
        void addMessageLine(std::string text);


        /// \brief Devuelve la posición X Y del puntero del ratón
        /// \return vec2f con las coordenadas x y
        vec2f getMousePosition();

        Gun* createGun(float px, float py, float pz);

        void update();

        tag::GraphicNode* cube01;

        int get_screenWidth(){return _screenWidth;};
        int get_screenHeight(){return _screenHeight;};

        tag::TAGEngine* getTagEngine() { return &m_tagEngine; }

        static const int _screenWidth  = 1000;
        static const int _screenHeight = 700;


    private:
        sf::RenderWindow*   m_window;
        sf::Font            m_font;
        sf::Text            m_messageLine[MAX_MESSAGE_LINES];



        sf::Clock           m_clock;
        float               m_secondsLastDraw;
        std::list<Node*>    m_scenes;
        Assimp::Importer    m_importer;   // OJO tiene que estar aqui, si es local da errores de memoria segmentation fault

        tag::GraphicNode*   m_camera;

        tag::TAGEngine      m_tagEngine;


        //scene::IAnimatedMeshSceneNode* createIrrAnimatedMeshSceneNode(std::string meshName);

        // Camara
        float tarUD;
        float tarLR;
        float zoomX;
        float zoomZ;
        static const unsigned short _camera_desviation  = 50;
        static const float          _camera_progression = 0.5f;
        static const int            _camera_y           = 250;
        static const int            _camera_z_offset    = -100;

        GraphicsEngine() {};

        void render();
    };
}

#define GEInstance dwe::GraphicsEngine::Instance()

#include "GraphicsEngineTemplates.cpp"  // La implementación de templates se tiene que incluir siempre en el h

#endif // FACHADEDIREENGINE_H
