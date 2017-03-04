#include "tag/TAGEngine.h"

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "tag/Entity.h"
#include "tag/ResourceManager.h"
#include "tag/ResourceMesh.h"

int tag::TAGEngine::m_aPositionLocation;
int tag::TAGEngine::m_aNormalLocation;
int tag::TAGEngine::m_uProjectionMatrixLocation;
int tag::TAGEngine::m_uMVMatrixLocation;
int tag::TAGEngine::m_uVMatrixLocation;
int tag::TAGEngine::m_uColorLocation;
int tag::TAGEngine::m_uLuz0Location;

tag::TAGEngine::TAGEngine()
{
    //ctor
}

tag::TAGEngine::~TAGEngine()
{
    //dtor
}

/////////////////////
void tag::TAGEngine::init()
{
    // Importante para que muestre bien el cubo y no haga un mal culling
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = false;

    m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Lab21", sf::Style::Default, contextSettings);

    // Habilita el z_buffer
   // glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Inicialización de GLEW
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // Carga de los Shaders
    Shader shader;
    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    shaders.push_back(shader.LoadShader("shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));

    m_shaderProgram = new Program(shaders);
    glUseProgram(m_shaderProgram->ReturnProgramID());

    // Attributes
    TAGEngine::m_aPositionLocation = m_shaderProgram->attrib(A_POSITION);
    TAGEngine::m_aNormalLocation   = m_shaderProgram->attrib(A_NORMAL);

    // Uniforms
    TAGEngine::m_uProjectionMatrixLocation   = m_shaderProgram->uniform(U_PROJECTIONMATRIX);
    TAGEngine::m_uMVMatrixLocation           = m_shaderProgram->uniform(U_MVMATRIX);
    TAGEngine::m_uVMatrixLocation            = m_shaderProgram->uniform(U_VMATRIX);
    TAGEngine::m_uColorLocation              = m_shaderProgram->uniform(U_COLOR);
    TAGEngine::m_uLuz0Location               = m_shaderProgram->uniform(U_LUZ0);


    // Estableciendo la matriz de proyección perspectiva
    glm::mat4 m_projectionMatrix = glm::perspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
    glUniformMatrix4fv(TAGEngine::m_uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

    // Creamos los mensajes de texto, por ahora vacios
    if (!m_font.loadFromFile("media/ExoRegular.otf"))
        throw std::runtime_error("No se ha podido cargar la fuente de texto");

	for(int i=0; i<MAX_MESSAGE_LINES; i++)
	{
        m_messageLine[i].setFont(m_font);
        m_messageLine[i].setCharacterSize(14);
        m_messageLine[i].setFillColor(sf::Color(255, 255, 255, 255));
        m_messageLine[i].setPosition(10.f, SCREEN_HEIGHT - (i+1)*16.f);
        m_messageLine[i].setString("");
	}

    m_secondsLastDraw = 0;
    m_clock.restart();
}

/////////////////////
bool tag::TAGEngine::isRunning()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
        // TODO faltan eventos de teclado
        /*else if (event.type == sf::Event::Resized)
        {
            glViewport(0, 0, event.size.width, event.size.height);
        }
        else
            receiver.OnEvent(event);*/
    }

    return m_window->isOpen();
}

/////////////////////
void tag::TAGEngine::draw()
{
    m_window->setActive(true);
    glm::mat4 rotateMatrix;
    glm::vec3 positionMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Cálculo de la vista (cámara)
    // TODO por ahora la posicion de la camara la establecemos aqui
    rotateMatrix = glm::mat4(1.0,0.0,0.0,0.0, 0.0,1.0,0.0,0.0, 0.0,0.0,1.0,0.0, 0.0,0.0,0.0,1.0);
    positionMatrix = glm::vec3(0.0, 0.0, -9.0);
    Entity::MVmatrix = glm::mat4();
    Entity::MVmatrix = glm::translate(Entity::MVmatrix, glm::vec3(positionMatrix[0], positionMatrix[1], positionMatrix[2]));
    Entity::MVmatrix = Entity::MVmatrix * rotateMatrix;
    Entity::MVmatrix = glm::scale(Entity::MVmatrix, glm::vec3(1.0, 1.0, 1.0));


    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(TAGEngine::m_aPositionLocation);
    glEnableVertexAttribArray(TAGEngine::m_aNormalLocation);
    glUseProgram(m_shaderProgram->ReturnProgramID());

    glUniform1i(TAGEngine::m_uLuz0Location, true);
    glUniformMatrix4fv(TAGEngine::m_uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(Entity::MVmatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar
    renderElements();

    glDisableVertexAttribArray(TAGEngine::m_aPositionLocation);
    glDisableVertexAttribArray(TAGEngine::m_aNormalLocation);
    glUseProgram(0);

    m_window->setActive(false);

    m_window->pushGLStates();
    for(unsigned int i=0; i<MAX_MESSAGE_LINES; i++)
        m_window->draw(m_messageLine[i]);
    m_window->popGLStates();

    m_window->display();

    char tmp[25];
    float fps = 1.f / (m_clock.getElapsedTime().asSeconds() - m_secondsLastDraw);
    m_secondsLastDraw = m_clock.getElapsedTime().asSeconds();
    sprintf(tmp, "Lab21 - fps:%f", fps);
    m_window->setTitle(tmp);
}

/////////////////////
void tag::TAGEngine::renderElements()
{
    resourceMesh->draw(vec3f(-2,0,0), vec3f(2,2,1));
    resourceMesh2->draw(vec3f(2,0,0), vec3f(1,0,1));
}


void tag::TAGEngine::createNode()
{
    resourceMesh = static_cast<ResourceMesh*>(m_resourceManager.getResource("media/newcube.obj"));
    resourceMesh2 = static_cast<ResourceMesh*>(m_resourceManager.getResource("media/newcube.obj"));
}

tag::ResourceManager tag::TAGEngine::getResourceManager()
{
    return m_resourceManager;
}
