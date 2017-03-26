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

    typedef NodeTemplate<const aiScene> Node;
    //irr: typedef NodeTemplate<ISceneNode> Node;
    //irr: typedef NodeTemplate<IAnimatedMeshSceneNode> Node;

    #include "GraphicsEngineTemplates.cpp"  // La implementación de templates se tiene que incluir siempre en el h

    // SFML FACHADA
    // ==============
    class Button{
        public:
            Button(std::string t, int x, int y);
            ~Button();
            void draw();
        private:
            //sf::Texture texture;
            //sf::RectangleShape background;
            sf::Font font;
            sf::Text text;
    };

    class Background{
        public:
            Background(std::string s);
            ~Background();
            void draw();
        private:
            sf::Texture texture;
            sf::RectangleShape rs;
    };

    class HudBox
    {
        public:
            HudBox(){};
            ~HudBox(){};
            virtual void draw(){};
            void setComponents(std::string str, sf::Sprite *s, sf::Texture *t, float px, float py);
            void setTextComponents(sf::Text *text, sf::Font font, unsigned int siz, sf::Color color, float px, float py);

        protected:
            float t;                  // Probar a cambiar de arma, vida, botiquines...
            sf::Font font;            // Fuente para los textos
    };

    class WeaponBox : public HudBox
    {
        public:
            WeaponBox(float x, float y);
            ~WeaponBox();
            void swapWeapon(sf::Texture *tweapon, sf::Text *textammo);
            void updateWeapon (sf::Texture *tweapon, std::string str, int *ammo, sf::Text *textammo);
            void draw();

        private:
            sf::Sprite s_box;
            sf::Texture t_box;

            sf::Sprite s_weapon;
            sf::Texture t_weapon;

            sf::Text text_ammo;

            // Variables para probar HUD
            int ammoGun;        // Para la munición de cada arma
            int ammoRifle;
            int ammoShotgun;
            int grenades;
    };

    class HealthBox : public HudBox
    {
        public:
            HealthBox(float x, float y);
            ~HealthBox();

            void drawCurrentHealth();
            void drawNumberOfHeals();
            void draw();


        private:

            // Caja base
            sf::Sprite s_box;
            sf::Texture t_box;

            // Vida
            sf::RectangleShape s_health;
            sf::Texture t_health;
            sf::Text text_health;

            // Vida perdida
            sf::Sprite s_hplost;
            sf::Texture t_hplost;

            // Contorno vida
            sf::Sprite s_edge;
            sf::Texture t_edge;

            // Botiquines
            sf::Sprite s_heal;
            sf::Texture t_heal;
            sf::Text text_heal;


            // Variables para probar el HUD al no tenerlo junto al Game
            int heals;      // Para los botiquines

            float health;     // Para la vida actual
            float max_health; // Para la vida máxima

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

        void init();
        void release();
        void close();
        bool isRunning();
        void draw();
        ///
        void drawRectangleShape(sf::RectangleShape rs);
        void drawText(sf::Text t);
        void drawSprite(sf::Sprite s);

        void clearWindow();
        void displayWindow();
        ///
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
        sf::Font            m_font;
        sf::Text            m_messageLine[MAX_MESSAGE_LINES];



        sf::Clock           m_clock;
        float               m_secondsLastDraw;
        Program*            m_shaderProgram;
        std::list<Node*>    m_scenes;
        Assimp::Importer    m_importer;   // OJO tiene que estar aqui, si es local da errores de memoria segmentation fault

        tag::TAGEngine      m_tagEngine;


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
