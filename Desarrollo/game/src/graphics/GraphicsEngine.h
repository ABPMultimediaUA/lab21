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
class Guardian;
class Legless;
class Mother;
class Entity;
class Door;
class Projectile;
class ProjectileGrenade;
class GrenadeExplosion;
class Generator;
class MagnetKey;
class SpeedBoost;
class Medkit;
class ScenaryElement;
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
        eAnimNone           =-1,

        eAnimPlayerStand    = 0,
        eAnimPlayerRun      = 1,
        eAnimPlayerStealth  = 2,    // Sigilo

        eAnimHumanoidStand  = 0,
        eAnimHumanoidDeath  = 1,

        eAnimLeglessStand   = 0,
        eAnimLeglessRun     = 1,
        eAnimLeglessDeath   = 2,
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
            T* getNode();
            void remove();

            bool intersects(Node* n);

            vec3f getBoundingBox();

            void setAnimation(AnimationType a);

            vec3f getTransformedBoundingBox();
            void setTransformedBoundingBox(vec3f v);

            void setActive(bool active);

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
        Player*     createMainPlayer();
        PlayerMate* createPlayerMate();
        Humanoid*   createEnemyHumanoid(int px, int py, int pz);
        Dog*        createEnemyDog(int px, int py, int pz);
        Bat*        createEnemyBat(int px, int py, int pz);
        Guardian*   createEnemyGuardian(int px, int py, int pz);
        Legless*    createEnemyLegless(int px, int py, int pz);
        Mother*     createEnemyMother(int px, int py, int pz);


        ScenaryElement* createWall(std::string meshName);

        //////////////////////////////
        // Eventos de teclado y ratón y logros
        AppReceiver receiver;
        AchievementsHandler achievementsHandler;

        void createCamera();
        void updateCamera(const vec3f playerPosition, int moreEnemiesX, int moreEnemiesZ);
        vec3f getCameraPosition();

        Door*               createDoor(int f, bool a, float px, float py, float pz);
        Projectile*         createProjectile(vec3f origin, float angle, std::string weapon);
        ProjectileGrenade*  createProjectileGrenade(vec3f origin, float angle);
        GrenadeExplosion*   createGrenadeExplosion(vec3f origin);
        Generator*          createGenerator(int i, bool b, float px, float py, float pz);
        MagnetKey*          createMagnetKey(int i, float px, float py, float pz);
        SpeedBoost*         createSpeedBoost(float px, float py, float pz);
        Medkit*             createMedkit(float px, float py, float pz);
        AmmoGun*            createAmmoGun(float px, float py, float pz);
        CShotgun*           createCShotgun(float px, float py, float pz);
        CRifle*             createCRifle(float px, float py, float pz);

        // weapons
        Gun*                createGun(Player* player);
        Shotgun*            createShotgun(Player* player);
        Rifle*              createRifle(Player* player);


        /// \brief Muestra un mensaje en la zona de mensajes
        /// \details Añade un mensaje a los mensajes que ya hay pasando los demás a lineas superiores y añadiendo
        /// el texto pasado a la línea más baja. Si se supera el número máximo de mensajes el de la fila superior
        /// se borrar. No admite acentos.
        /// \param[in] text Texto a mostrar en la lista de mensajes
        void addMessageLine(std::string text);

        /// \brief Devuelve la posición X Y del puntero del ratón
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
        uint16_t            m_drawsCount;
        float               m_timeIniDraw;
        float               m_timeAccumDraw;
        Program*            m_shaderProgram;
        std::list<Node*>    m_scenes;
        Assimp::Importer    m_importer;   // OJO tiene que estar aqui, si es local da errores de memoria segmentation fault

        tag::TAGEngine      m_tagEngine;
        tag::GraphicNode*   m_camera;
        vec3f               m_cameraPosition;

#ifndef LAB21_DEBUG
        static const int _screenWidth   = 1024;
        static const int _screenHeight  = 768;
        static const bool _fullScreen   = true;
#else
        static const int _screenWidth   = 1024;
        static const int _screenHeight  = 768;
        static const bool _fullScreen   = false;
#endif
        // Camara
        float tarUD;
        float tarLR;
        float zoomX;
        float zoomZ;
        static const uint8_t    _camera_desviation  = 50;
        static const uint8_t    _camera_progression = 1;
        static const uint8_t    _camera_border      = 50;
        static const uint16_t   _camera_y           = 350;
        static const uint16_t   _camera_z_offset    = 100;

        GraphicsEngine() {};

        void render();
    };
}

#define GEInstance dwe::GraphicsEngine::Instance()

#include "GraphicsEngineTemplates.cpp"  // La implementación de templates se tiene que incluir siempre en el h

#endif // FACHADEDIREENGINE_H
