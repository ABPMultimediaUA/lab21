#ifndef FACHADEDIREENGINE_H
#define FACHADEDIREENGINE_H

#define GLEW_STATIC
#include<GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <math.h>
#include <string>
#include <list>

#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

#include "AppReceiver.h"
#include "AchievementsHandler.h"
#include "tag/ResourceMesh.h"
#include "tag/TAGEngine.h"
#include "tag/GraphicNode.h"
#include "AnimatedSprite.hpp"


#define MAX_MESSAGE_LINES 4

using namespace std;


class BaseDireWReplica;
class Player;
class PlayerMate;
class Humanoid;
class Dog;
class Bat;
class Entity;
class Door;
class Projectile;
class ProjectileGrenade;
class Generator;
class MagnetKey;
class SpeedBoost;
class Medkit;
class ScenaryElement;
class Trigger;
class TriggerDoor;
class TriggerGenerator;
class CShotgun;
class CRifle;
class Gun;
class Shotgun;
class Rifle;
class AmmoGun;
class Program;

namespace dwe
{

    ///////////////////////////////////////////////
    // AnimationType
    // =============
    ///////////////////////////////////////////////
    enum AnimationType {
        eAnimNone,
        eAnimStand,
        eAnimWalk,
        eAnimRun,
        eAnimAttack
    };


    ///////////////////////////////////////////////
    // vectores
    // ========
    ///////////////////////////////////////////////
    typedef tag::vec2f vec2f;
    typedef tag::vec2i vec2i;
    typedef tag::vec3f vec3f;


    ///////////////////////////////////////////////
    // Node
    // ====
    ///////////////////////////////////////////////
    //typedef Node;  // Lo defino como typedef despues del NodeTemplate
    template <class T> class NodeTemplate;
    typedef NodeTemplate<tag::GraphicNode> Node;

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
            void remove();

            bool intersects(Node* n);

            vec3f getBoundingBox();

            void setAnimation(AnimationType a);

            vec3f getTransformedBoundingBox();
            void setTransformedBoundingBox(vec3f v);

        private:
            T* m_node;
            vec3f       m_position;
            vec3f       m_rotation;
            float       m_color[4];
    };





    ///////////////////////////////////////////////
    // GraphicsEngine
    // ==============
    ///////////////////////////////////////////////
    class GraphicsEngine
    {
    public:
        static GraphicsEngine* Instance();

        void init();
        void release();
        void close();
        bool isRunning();
        bool getWindowClose();
        void draw();
        ///
        void drawRectangleShape(sf::RectangleShape rs);
        void drawText(sf::Text t);
        void drawSprite(sf::Sprite sp);
        void drawAnimatedSprite(AnimatedSprite as);

        void clearWindow();
        void displayWindow();
        ///
        Node* createNode(std::string meshName);

        // Creacion de personajes
        Player* createMainPlayer(Gun* gun);
        PlayerMate* createPlayerMate();
        Humanoid* createEnemyHumanoid(int px, int py, int pz);
        Dog* createEnemyDog(int px, int py, int pz);
        Bat* createEnemyBat(int px, int py, int pz);

        ScenaryElement* createWall(std::string meshName);

        //////////////////////////////
        // Eventos de teclado y rat�n y logros
        AppReceiver receiver;
        AchievementsHandler achievementsHandler;

        void createCamera();
        void updateCamera(const vec3f playerPosition, int moreEnemiesX, int moreEnemiesZ);

        Door* createDoor(int f, bool a, float px, float py, float pz);
        Projectile* createProjectile(vec3f origin, float angle, std::string weapon);
        ProjectileGrenade* createProjectileGrenade(vec3f origin, float angle);
        Generator* createGenerator(int i, bool b, float px, float py, float pz);
        MagnetKey* createMagnetKey(int i, float px, float py, float pz);
        SpeedBoost* createSpeedBoost(float px, float py, float pz);
        Medkit* createMedkit(float px, float py, float pz);
        TriggerDoor* createTriggerDoor(float px, float py, float pz);
        TriggerGenerator* createTriggerGenerator(float px, float py, float pz);
        AmmoGun* createAmmoGun(float px, float py, float pz);
        CShotgun* createCShotgun(float px, float py, float pz);
        CRifle* createCRifle(float px, float py, float pz);
        Gun* createGun(float px, float py, float pz);
        Shotgun* createShotgun(float px, float py, float pz);
        Rifle* createRifle(float px, float py, float pz);


        /// \brief Muestra un mensaje en la zona de mensajes
        /// \details A�ade un mensaje a los mensajes que ya hay pasando los dem�s a lineas superiores y a�adiendo
        /// el texto pasado a la l�nea m�s baja. Si se supera el n�mero m�ximo de mensajes el de la fila superior
        /// se borrar. No admite acentos.
        /// \param[in] text Texto a mostrar en la lista de mensajes
        void addMessageLine(std::string text);

        /// \brief Devuelve la posici�n X Y del puntero del rat�n
        /// \return vec2f con las coordenadas x y
        vec2f getMousePosition();

         class GETexture : public sf::Texture { // Para el hud

         } ;

        int get_screenWidth(){return _screenWidth;};
        int get_screenHeight(){return _screenHeight;};

        tag::TAGEngine* getTagEngine() { return &m_tagEngine; }

        void push();
        void pop();

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
        tag::GraphicNode*   m_camera;


        static const int _screenWidth  = 1000;
        static const int _screenHeight = 700;

        // Camara
        float tarUD;
        float tarLR;
        float zoomX;
        float zoomZ;
        static const unsigned short _camera_desviation  = 50;
        static const float          _camera_progression = 0.5f;
        static const int            _camera_y           = 350;
        static const int            _camera_z_offset    = 100;

        GraphicsEngine() {};

        void render();
    };
}

#define GEInstance dwe::GraphicsEngine::Instance()

#include "GraphicsEngineTemplates.cpp"  // La implementaci�n de templates se tiene que incluir siempre en el h

#endif // FACHADEDIREENGINE_H
