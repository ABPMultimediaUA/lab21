#define GLEW_STATIC
#include<GL/glew.h>

#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Scene.h"
#include "GraphicsEngine.h"
#include "Player.h"




#include "tag/GraphicNode.h"
#include "tag/EMesh.h"
#include "tag/ResourceManager.h"
#include "tag/ResourceMesh.h"
#include "tag/ETransform.h"
#include "tag/TAGEngine.h"


using namespace tag;

int main()
{
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
    entity06.loadMesh("malla6.obj");
    entity06.m_cadena = "06 - MESH";
    nodo06.setEntity(&entity06);
    nodo04.addChild(&nodo06);

    tag::GraphicNode nodo07;
    tag::EMesh entity07;
    entity07.loadMesh("malla7.obj");
    entity07.m_cadena = "07 - MESH";
    nodo07.setEntity(&entity07);
    nodo04.addChild(&nodo07);

    /////////////////////////////////////
    // Transformaciones
    /////////////////////////////////////
    transform01.identity();
    transform01.rotate(90, 0, 0);
    //transform01.translate(3, 2, 4);


   /* transform02.load(glm::mat4(1, 2, 3, 4, 2, 4, 1, 2, 2, 1, 3, 4, 4, 1, 3, 2));
    transform02.transpose();

    transform03.identity();
    transform03.rotate(dwe::vec3f(180, 0, 90));
    transform03.translate(dwe::vec3f(2, 3, 4));*/

    transform04.translate(2, 3, 4);

    nodoRoot.draw();



    //return 0;


    //               Root
    //          /      |     \
    //        1        2      3
    //      /   \     /      /
    //    4      5   9      10
    //  /  \    /          /  \
    // 6   7   8         11   12
    //
    // Salida:
    // Begin Root
    // Begin 01
    // Begin 04
    // Begin 06
    // End 06
    // Begin 07
    // End 07
    // End 04
    // Begin 05
    // Begin 08
    // End 08
    // End 05
    // End 01
    // Begin 02
    // Begin 09
    // End 09
    // End 02
    // Begin 03
    // Begin 10
    // Begin 11
    // End 11
    // Begin 12
    // End 12
    // End 10
    // End 03
    // End Root
    /////////////////////////////////////

    std::cout << "//////////////////////////////////////////\n// Probando resourcemanager\n////////////////////////////\n";

//    ResourceManager resourceManager;
//    ResourceMesh* resourceMesh;

//    resourceMesh = static_cast<ResourceMesh*>(resourceManager.getResource("media/newcube.obj"));
//    resourceManager.getResource("media/newcube.obj");
//    resourceManager.getResource("media/newcube.obj");
//    resourceManager.getResource("media/newcube.obj");
//    resourceManager.getResource("media/newcube.obj");
//    resourceManager.getResource("media/newcube.obj");

    TAGEngine tagEngine;
    tagEngine.init();
    tagEngine.createNode();
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
