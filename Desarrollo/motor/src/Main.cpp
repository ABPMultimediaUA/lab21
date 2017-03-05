#define GLEW_STATIC
#include<GL/glew.h>

#include "Scene.h"
#include "GraphicsEngine.h"
#include "Player.h"


#include "tag/GraphicNode.h"




using namespace tag;

int main()
{
    TAGEngine tagEngine;
    tagEngine.init();

    GraphicNode* cube01 = tagEngine.createMesh("media/newcube.obj", vec3f(-2,0,0), vec3f(2,2,1));
    GraphicNode* cube02 = tagEngine.createMesh("media/newcube.obj", vec3f( 2,0,0), vec3f(0,2,0));
    GraphicNode* cube03 = tagEngine.createMesh("media/newcube.obj", vec3f( 0,-2.2,0), vec3f(0,0,0), cube02);

    GraphicNode* camera = tagEngine.createPerspectiveCamera(vec3f(0,0,-9.0), vec3f(0,0,0), 45.0f, TAGEngine::screenWidth / TAGEngine::screenHeight, 0.1f, 1000.0f);

    while (tagEngine.isRunning())
    {
        tagEngine.draw();
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
