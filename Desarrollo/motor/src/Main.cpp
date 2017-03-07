#define GLEW_STATIC
#include<GL/glew.h>

#include "Scene.h"
#include "GraphicsEngine.h"
#include "Player.h"


#include "tag/GraphicNode.h"
<<<<<<< HEAD
#include "tag/EMesh.h"
#include "tag/ResourceManager.h"
#include "tag/ResourceMesh.h"
#include "tag/ETransform.h"
#include "tag/TAGEngine.h"
#include "tag/EAnimation.h"
=======


>>>>>>> master


using namespace tag;

int main()
{
<<<<<<< HEAD

    /////////////////////////////////////
    // Creacion del arbol
    /////////////////////////////////////
    tag::GraphicNode nodoRoot;
    tag::EMesh entityRoot;
    entityRoot.m_cadena = "Root";
    nodoRoot.setEntity(&entityRoot);

    tag::GraphicNode nodo01;
    tag::ETransform transform01;
    transform01.m_cadena = "01 - MATRIX";
    nodo01.setEntity(&transform01);
    nodoRoot.addChild(&nodo01);

    tag::GraphicNode nodo04;
    tag::ETransform transform04;
    transform04.m_cadena = "04 - MATRIX";
    nodo04.setEntity(&transform04);
    nodo01.addChild(&nodo04);

    tag::GraphicNode nodo06;
    tag::EMesh entity06;
    entity06.loadMesh("media/newcube.obj");
    entity06.m_cadena = "06 - MESH";
    nodo06.setEntity(&entity06);
    nodo04.addChild(&nodo06);

    tag::GraphicNode nodo07;
    tag::EMesh entity07;
    entity07.loadMesh("media/newcube.obj");
    entity07.m_cadena = "07 - MESH";
    nodo07.setEntity(&entity07);
    nodo04.addChild(&nodo07);

    tag::GraphicNode nodo08;
    tag::EAnimation entity08;
    entity08.loadFrame("media/newcube.obj", 1);
    entity08.m_cadena = "08 - ANIMATEDMESH";
    nodo08.setEntity(&entity08);
    nodo04.addChild(&nodo08);

    /////////////////////////////////////
    // Transformaciones
    /////////////////////////////////////
    transform01.rotate(90, 0, 0);

    transform04.translate(2, 3, 4);

    nodoRoot.draw();

/*
              root
               /
               1
               /
               4
              /|\
             6 7 8

*/

=======
>>>>>>> master
    TAGEngine tagEngine;
    tagEngine.init();

    GraphicNode* cube01 = tagEngine.createMesh("media/newcube.obj", vec3f(-2,0,0), vec3f(2,45,1));
    GraphicNode* cube02 = tagEngine.createMesh("media/newcube.obj", vec3f( 2,0,0), vec3f(0,20,0));
    GraphicNode* cube03 = tagEngine.createMesh("media/newcube.obj", vec3f( 0,-2.2,0), vec3f(0,0,0), cube02);

    GraphicNode* camera = tagEngine.createPerspectiveCamera(vec3f(2,0,-9.0), vec3f(0,0,0), 45.0f, TAGEngine::screenWidth / TAGEngine::screenHeight, 0.1f, 1000.0f);

    GraphicNode* light  = tagEngine.createLight(vec3f(-100,100,50), vec3f(0,0,0));

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
