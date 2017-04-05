#define GLEW_STATIC
#include<GL/glew.h>
#include <glm/glm.hpp>

#include "GraphicsEngine.h"


#include <iostream>
#include <vector>

#include "AppReceiver.h"
#include "Scene.h"
#include "Shader.h"
#include "Program.h"

#include "Player.h"
#include "Gun.h"

#include "tag/TAGEngine.h"
#include "tag/GraphicNode.h"

///////////////////////////////////////////////
// class GraphicsEngine
///////////////////////////////////////////////
dwe::GraphicsEngine* dwe::GraphicsEngine::Instance()
{
    static GraphicsEngine instance;
    return &instance;
}

//////////////////////////
void dwe::GraphicsEngine::init()
{
    // Importante para que muestre bien el cubo y no haga un mal culling
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = false;

    m_window = new sf::RenderWindow(sf::VideoMode(GraphicsEngine::_screenWidth, GraphicsEngine::_screenHeight), "Lab21", sf::Style::Default, contextSettings);
    m_tagEngine.init(GraphicsEngine::_screenHeight, GraphicsEngine::_screenWidth);
}


//////////////////////////
void dwe::GraphicsEngine::draw()
{
    m_tagEngine.draw();

    m_window->pushGLStates();
    m_window->draw(m_messageLine[0]);
    m_window->popGLStates();

    m_window->display();
}

//////////////////////////
void dwe::GraphicsEngine::createCamera()
{
    m_tagEngine.createPerspectiveCamera(vec3f(2,0,60), vec3f(0,0,0), 45.0f, dwe::GraphicsEngine::_screenWidth / dwe::GraphicsEngine::_screenHeight, 0.1f, 1000.0f);
    m_tagEngine.createLight(vec3f(-10,0,50), vec3f(0,0,0));

    m_tagEngine.createMesh("media/perro.obj", vec3f(-10,0,0), vec3f(0,-45,0));
    m_tagEngine.createMesh("media/perro.obj", vec3f(10,0,0), vec3f(0,-45,0), "media/perro.bmp");
    m_tagEngine.createMesh("media/perro.obj", vec3f(15,0,0), vec3f(0,-45,0), "media/perro2.bmp");
}
