#define GLEW_STATIC
#include<GL/glew.h>

#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Scene.h"
#include "GraphicsEngine.h"
#include "Player.h"


#include "tag/GraphicNode.h"
#include "tag/ResourceManager.h"
#include "tag/ResourceMesh.h"
#include "tag/EMesh.h"
#include "tag/ETransform.h"
#include "tag/ECamera.h"
#include "tag/ELight.h"
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
    transform01.m_cadena = "01 - T_MATRIX";
    nodo01.setEntity(&transform01);
    nodoRoot.addChild(&nodo01);

    tag::GraphicNode nodo02;
    tag::ETransform transform02;
    transform02.m_cadena = "02 - T_MATRIX";
    nodo02.setEntity(&transform02);
    nodoRoot.addChild(&nodo02);

    tag::GraphicNode nodo03;
    tag::ETransform transform03;
    transform03.m_cadena = "03 - T_MATRIX";
    nodo03.setEntity(&transform03);
    nodoRoot.addChild(&nodo03);

    tag::GraphicNode nodo04;
    tag::ETransform transform04;
    transform04.m_cadena = "04 - T_MATRIX";
    nodo04.setEntity(&transform04);
    nodo01.addChild(&nodo04);

    tag::GraphicNode nodo05;
    tag::ETransform transform05;
    transform05.m_cadena = "05 - T_MATRIX";
    nodo05.setEntity(&transform05);
    nodo02.addChild(&nodo05);

    tag::GraphicNode nodo06;
    tag::ETransform transform06;
    transform06.m_cadena = "06 - T_MATRIX";
    nodo06.setEntity(&transform06);
    nodo03.addChild(&nodo06);

    tag::GraphicNode nodo07;
    tag::EMesh entity07;
    entity07.loadMesh("media/newcube.obj");
    entity07.m_cadena = "07 - MESH";
    nodo07.setEntity(&entity07);
    nodo04.addChild(&nodo07);

    tag::GraphicNode nodo08;
    tag::EMesh entity08;
    entity08.loadMesh("media/newcube.obj");
    entity08.m_cadena = "08 - MESH";
    nodo08.setEntity(&entity08);
    nodo04.addChild(&nodo08);

    tag::GraphicNode nodo09;
    tag::ECamera camera;
    //camera.setActive(true);
    camera.m_cadena = " 09 - CAMERA";
    nodo09.setEntity(&camera);
    nodo05.addChild(&nodo09);

    tag::GraphicNode nodo10;
    tag::ELight light;
    light.m_cadena = "10 - LIGHT";
    nodo10.setEntity(&light);
    nodo06.addChild(&nodo10);

    /////////////////////////////////////
    // Transformaciones
    /////////////////////////////////////
    transform01.rotate(90, 0, 0);

    transform04.translate(2, 3, 4);

    nodoRoot.draw();

/****************************** Árbol *****************************

                  root
            /       |      \               t : transformación
           1t       2t     3t              m : malla
           |        |      |               c : cámara
          4t        5t     6t              l : luz
        /   \       |       |
       7     8      9      10
       |     |      |       |
       m     m      c       l

*******************************************************************/

    TAGEngine tagEngine;
    tagEngine.init();

    std::cout << "\n\n\nCargamos mallas: \n--------------------\n";

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
