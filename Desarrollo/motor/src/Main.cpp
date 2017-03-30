#define GLEW_STATIC
#include<GL/glew.h>

#include "Scene.h"
#include "GraphicsEngine.h"
#include "Player.h"
#include "Gun.h"


#include "tag/GraphicNode.h"
#include "tag/TAGEngine.h"


using namespace tag;

int main()
{
   /* GEInstance->init();

    GEInstance->createCamera();
    GEInstance->updateCamera(vec3f(0,0,0), 0, 0);

    Gun* g = GEInstance->createGun(0,0,0);
    Player* player = GEInstance->createMainPlayer(g);

    Player* player2 = GEInstance->createMainPlayer(g);
    player2->setPosition(vec3f(30,0,0));

    dwe::Node* suelo;
    suelo = GEInstance->createNode("media/unitySuelo_300x50");
    suelo->setRotation(dwe::vec3f(0,0,0));
    suelo->setPosition(dwe::vec3f(0,0,0));

    while (GEInstance->isRunning())
    {
        GEInstance->update();
        //player->setPosition(vec3f(player->getPosition().x+0.01, player->getPosition().y, player->getPosition().z-0.01));
        //GEInstance->updateCamera(player->getPosition(), 5, 0);
        GEInstance->draw();
    }

    return 0;*/

    GEInstance->init();
    //GEInstance->addMessageLine("Holaaa");
    TAGEngine* tagEngine = GEInstance->getTagEngine();

    GraphicNode* camera = tagEngine->createPerspectiveCamera(vec3f(2,0,60), vec3f(0,0,0), 45.0f, dwe::GraphicsEngine::_screenWidth / dwe::GraphicsEngine::_screenHeight, 0.1f, 1000.0f);
    GraphicNode* light  = tagEngine->createLight(vec3f(-10,0,-80), vec3f(0,0,0));

    GraphicNode* perro = tagEngine->createMesh("media/perro.obj", vec3f(-10,0,0), vec3f(0,-45,0));
    GraphicNode* perro2 = tagEngine->createMesh("media/perro.obj", vec3f(10,0,0), vec3f(0,-45,0), "media/perro.bmp");
    GraphicNode* perro3 = tagEngine->createMesh("media/perro.obj", vec3f(15,0,0), vec3f(0,-45,0), "media/perro2.bmp");


    while (GEInstance->isRunning())
    {
        GEInstance->draw();
    }

    return 0;


    ///////////////////////////////////


/*
    GEInstance->init();

    Player* mainPlayer = GEInstance->createMainPlayer();

    GEInstance->addMessageLine("Gestor de ventanas con SFML");
    GEInstance->addMessageLine("Carga de modelos con ASSIMP");
    GEInstance->addMessageLine("Rotar con teclas A D W S");
    GEInstance->addMessageLine("Movimiento con ratón");

    while (GEInstance->isRunning())
    {
        dwe::vec3f rotation = mainPlayer->getRotation();
        if(GEInstance->receiver.isKeyDown(KEY_KEY_A))
            rotation.y -= 0.0005;
        else if(GEInstance->receiver.isKeyDown(KEY_KEY_D))
            rotation.y += 0.0005;
        else if(GEInstance->receiver.isKeyDown(KEY_KEY_W))
            rotation.x -= 0.0005;
        else if(GEInstance->receiver.isKeyDown(KEY_KEY_S))
            rotation.x += 0.0005;
        mainPlayer->setRotation(rotation);

        dwe::vec3f position = mainPlayer->getPosition();
        dwe::vec2f mousePos = GEInstance->getMousePosition();
        position.x = (mousePos.x - SCREEN_WIDTH/2)/80.0;
        position.y = (mousePos.y + SCREEN_HEIGHT/2)/80.0;
        mainPlayer->setPosition(position);

        GEInstance->draw();
    }

    return 0;*/
}
