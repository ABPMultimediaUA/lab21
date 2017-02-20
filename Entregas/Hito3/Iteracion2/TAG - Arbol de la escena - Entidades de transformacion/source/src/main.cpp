#define GLEW_STATIC
#include<GL/glew.h>

#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Scene.h"
#include "GraphicsEngine.h"


using namespace dwe;

int main()
{
    /////////////////////////////////////
    // Creacion del arbol
    /////////////////////////////////////
    dwe::GraphicNode nodoRoot;
    dwe::EMesh entityRoot;
    entityRoot.m_cadena = "Root";
    nodoRoot.setEntity(&entityRoot);

    dwe::GraphicNode nodo01;
    dwe::ETransform transform01;
    transform01.m_cadena = "01 - MATRIX";
    nodo01.setEntity(&transform01);
    nodoRoot.addChild(&nodo01);

    dwe::GraphicNode nodo02;
    dwe::ETransform transform02;
    transform02.m_cadena = "02 - MATRIX";
    nodo02.setEntity(&transform02);
    nodoRoot.addChild(&nodo02);

    dwe::GraphicNode nodo03;
    dwe::ETransform transform03;
    transform03.m_cadena = "03 - MATRIX";
    nodo03.setEntity(&transform03);
    nodoRoot.addChild(&nodo03);

    dwe::GraphicNode nodo04;
    dwe::EMesh entity04;
    entity04.m_cadena = "04";
    nodo04.setEntity(&entity04);
    nodo01.addChild(&nodo04);

    dwe::GraphicNode nodo05;
    dwe::EMesh entity05;
    entity05.m_cadena = "05";
    nodo05.setEntity(&entity05);
    nodo01.addChild(&nodo05);

    dwe::GraphicNode nodo06;
    dwe::EMesh entity06;
    entity06.m_cadena = "06";
    nodo06.setEntity(&entity06);
    nodo04.addChild(&nodo06);

    dwe::GraphicNode nodo07;
    dwe::EMesh entity07;
    entity07.m_cadena = "07";
    nodo07.setEntity(&entity07);
    nodo04.addChild(&nodo07);

    dwe::GraphicNode nodo08;
    dwe::EMesh entity08;
    entity08.m_cadena = "08";
    nodo08.setEntity(&entity08);
    nodo05.addChild(&nodo08);

    dwe::GraphicNode nodo09;
    dwe::EMesh entity09;
    entity09.m_cadena = "09";
    nodo09.setEntity(&entity09);
    nodo02.addChild(&nodo09);

    dwe::GraphicNode nodo10;
    dwe::EMesh entity10;
    entity10.m_cadena = "10";
    nodo10.setEntity(&entity10);
    nodo03.addChild(&nodo10);

    dwe::GraphicNode nodo11;
    dwe::EMesh entity11;
    entity11.m_cadena = "11";
    nodo11.setEntity(&entity11);
    nodo10.addChild(&nodo11);

    dwe::GraphicNode nodo12;
    dwe::EMesh entity12;
    entity12.m_cadena = "12";
    nodo12.setEntity(&entity12);
    nodo10.addChild(&nodo12);

    /////////////////////////////////////
    // Transformaciones
    /////////////////////////////////////
    transform01.identity();
    transform01.rotate(90, 0, 0);
    transform01.translate(3, 2, 4);

    transform02.load(glm::mat4(1, 2, 3, 4, 2, 4, 1, 2, 2, 1, 3, 4, 4, 1, 3, 2));
    transform02.transpose();

    transform03.identity();
    transform03.rotate(dwe::vec3f(180, 0, 90));
    transform03.translate(dwe::vec3f(2, 3, 4));

    nodoRoot.draw();

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


    return 0;
}
