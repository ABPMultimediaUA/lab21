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
        void draw();
        void createElements();

        tag::TAGEngine* getTagEngine() { return &m_tagEngine; }


        static const int _screenWidth  = 1000;
        static const int _screenHeight = 700;

        AppReceiver receiver;

    private:
        sf::RenderWindow*   m_window;
        sf::Font            m_font;
        sf::Text            m_messageLine[MAX_MESSAGE_LINES];

        Assimp::Importer    m_importer;   // OJO tiene que estar aqui, si es local da errores de memoria segmentation fault

        tag::GraphicNode*   m_camera;

        tag::TAGEngine      m_tagEngine;


        GraphicsEngine() {};

    };
}

#define GEInstance dwe::GraphicsEngine::Instance()

#include "GraphicsEngineTemplates.cpp"  // La implementación de templates se tiene que incluir siempre en el h

#endif // FACHADEDIREENGINE_H
