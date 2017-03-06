#include "tag/TAGEngine.h"

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "tag/Entity.h"
#include "tag/ResourceMesh.h"
#include "tag/ECamera.h"
#include "tag/ELight.h"
#include "tag/ETransform.h"
#include "tag/EMesh.h"

int tag::TAGEngine::m_aPositionLocation;
int tag::TAGEngine::m_aNormalLocation;
int tag::TAGEngine::m_uProjectionMatrixLocation;
int tag::TAGEngine::m_uMVMatrixLocation;
int tag::TAGEngine::m_uLMatrixLocation;
int tag::TAGEngine::m_uColorLocation;
int tag::TAGEngine::m_uLuz0Location;

const float tag::TAGEngine::screenHeight;
const float tag::TAGEngine::screenWidth;


tag::TAGEngine::TAGEngine() :
    m_rootNode(),
    m_cameras(),
    m_lights(),
    m_numActiveCamera(0)
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
    glEnable(GL_DEPTH_TEST);
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
    TAGEngine::m_uLMatrixLocation            = m_shaderProgram->uniform(U_LMATRIX);
    TAGEngine::m_uColorLocation              = m_shaderProgram->uniform(U_COLOR);
    TAGEngine::m_uLuz0Location               = m_shaderProgram->uniform(U_LUZ0);


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

    // El cálculo de la vista (cámara) se realiza en el setActiveCamera.

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(TAGEngine::m_aPositionLocation);
    glEnableVertexAttribArray(TAGEngine::m_aNormalLocation);
    glUseProgram(m_shaderProgram->ReturnProgramID());


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
    // Recorremos el arbol llamando al draw
    m_rootNode.draw();
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createNodeTransform(GraphicNode* parent)
{
    GraphicNode* nodoTransform = new GraphicNode();
    ETransform* etransform = new ETransform();
    nodoTransform->setEntity(etransform);
    parent->addChild(nodoTransform);

    return nodoTransform;
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createNodeRotation(const vec3f rotation, GraphicNode* parent)
{
    GraphicNode* nodoRotacion = createNodeTransform(parent);
    static_cast<ETransform*>(nodoRotacion->getEntity())->rotate(rotation);

    return nodoRotacion;
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createNodePosition(const vec3f position, GraphicNode* parent)
{
    GraphicNode* nodoPosition = createNodeTransform(parent);
    static_cast<ETransform*>(nodoPosition->getEntity())->translate(position);

    return nodoPosition;
}

////////////////////////////
tag::GraphicNode* tag::TAGEngine::createMesh(const std::string fileName, const vec3f position, const vec3f rotation, GraphicNode* parent)
{
    // Si no especificamos padre, usamos el root. 0 es el valor por defecto
    if (parent==0)
        parent = &m_rootNode;


    // Creamos nodo de traslación (posición)
    GraphicNode* nodoTraslacion = createNodePosition(position, parent);

    // Creamos nodo de Rotación
    GraphicNode* nodoRotacion = createNodeRotation(rotation, nodoTraslacion);


    // Creamos nodo de malla
    GraphicNode* nodoMalla = new GraphicNode();
    EMesh* malla = new EMesh();
    nodoMalla->setEntity(malla);
    malla->loadMesh(fileName);

    nodoRotacion->addChild(nodoMalla);

    return nodoMalla;
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createPerspectiveCamera(const vec3f position, const vec3f rotation, float fov, float aspect, float near, float far, GraphicNode* parent)
{
    // Si no especificamos padre, usamos el root. 0 es el valor por defecto
    if (parent==0)
        parent = &m_rootNode;

    // Creamos nodo de traslación (posición)
    GraphicNode* nodoTraslacion = createNodePosition(position, parent);

    // Creamos nodo de Rotación
    GraphicNode* nodoRotacion = createNodeRotation(rotation, nodoTraslacion);

    // Creamos nodo de cámara
    GraphicNode* nodoCam = new GraphicNode();
    ECamera* cam = new ECamera();
    cam->setPerspective(fov, aspect, near, far);
    nodoCam->setEntity(cam);

    nodoRotacion->addChild(nodoCam);

    // Registramos la cámara
    m_cameras.push_back(nodoCam);


    // Activo la cámara recien creada si no hay ninguna activa
    if (m_numActiveCamera == 0)
    {
        setActiveCamera(m_cameras.size());
    }

    return nodoCam;
}

/////////////////////
void tag::TAGEngine::setActiveCamera(const unsigned int activeCamera)
{
    // TODO controlar si la camara no existe o es cero
    m_numActiveCamera = activeCamera;

    // Obtenemos el nodo
    GraphicNode* nodeCam = m_cameras.at(m_numActiveCamera-1);

    // Estableciendo la matriz de proyección perspectiva
    glm::mat4 m_projectionMatrix = static_cast<ECamera*>(nodeCam->getEntity())->getProjectionMatrix();
    glUniformMatrix4fv(TAGEngine::m_uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

    // Calculamos Entity::viewMatrix
    // Recorremos hasta root guardando todas las transformaciones.
    std::stack<glm::mat4> pila;
    GraphicNode* node = nodeCam;

    while (node=node->getParent())
    {
        Entity* entity = node->getEntity();

        // Si hace un cast no válido, devuelve nulo
        if (ETransform* t = dynamic_cast<ETransform*>(entity))
            pila.push(t->getMatrix());
    }

    // Aplicamos las transformaciones sacando de la pila
    Entity::viewMatrix = glm::mat4();
    while (pila.size()>0)
    {
        Entity::viewMatrix *= pila.top();
        pila.pop();
    }
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createLight(const vec3f position, const vec3f rotation, GraphicNode* parent)
{
    // Si no especificamos padre, usamos el root. 0 es el valor por defecto
    if (parent==0)
        parent = &m_rootNode;

    // Creamos nodo de traslación (posición)
    GraphicNode* nodoTraslacion = createNodePosition(position, parent);

    // Creamos nodo de Rotación
    GraphicNode* nodoRotacion = createNodeRotation(rotation, nodoTraslacion);

    // Creamos nodo de luz
    GraphicNode* nodoLuz = new GraphicNode();
    ELight* luz = new ELight();

    nodoLuz->setEntity(luz);

    nodoRotacion->addChild(nodoLuz);

    // Registramos la cámara
    m_lights.push_back(nodoLuz);

    setLightOn(m_lights.size());

    return nodoLuz;
}

void tag::TAGEngine::setLightOn(const unsigned int light)
{
    // Obtenemos el nodo
    GraphicNode* nodeLuz = m_lights.at(light-1);

    glUniform1i(TAGEngine::m_uLuz0Location, true);


    // Calculamos Entity::viewMatrix
    // Recorremos hasta root guardando todas las transformaciones.
    std::stack<glm::mat4> pila;
    GraphicNode* node = nodeLuz;

    while (node=node->getParent())
    {
        Entity* entity = node->getEntity();

        // Si hace un cast no válido, devuelve nulo
        if (ETransform* t = dynamic_cast<ETransform*>(entity))
            pila.push(t->getMatrix());
    }

    // Aplicamos las transformaciones sacando de la pila
    glm::mat4 lMatrix;
    while (pila.size()>0)
    {
        lMatrix *= pila.top();
        pila.pop();
    }

    glUniformMatrix4fv(TAGEngine::m_uLMatrixLocation, 1, GL_FALSE, glm::value_ptr(lMatrix)); // Para la luz matrix view pero sin escalado!

}
