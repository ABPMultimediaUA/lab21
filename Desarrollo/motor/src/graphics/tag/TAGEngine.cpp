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
    m_lights(),
    m_cameras(),
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
}

/////////////////////
bool tag::TAGEngine::isRunning()
{
    return true;
}

/////////////////////
void tag::TAGEngine::draw()
{
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

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createNodePR(const vec3f position, const vec3f rotation, GraphicNode* parent)
{
    // Si no especificamos padre, usamos el root. 0 es el valor por defecto
    if (parent==0)
        parent = &m_rootNode;

    // Creamos nodo de Rotación
    GraphicNode* nodoRotacion = createNodeRotation(rotation, parent);

    // Creamos nodo de traslación (posición)
    GraphicNode* nodoTraslacion = createNodePosition(position, nodoRotacion);

    // Cremamos nodo final
    GraphicNode* nodo = new GraphicNode();
    nodoTraslacion->addChild(nodo);

    return nodo;
}

////////////////////////////
tag::GraphicNode* tag::TAGEngine::createMesh(const std::string fileName, const vec3f position, const vec3f rotation, GraphicNode* parent)
{
    // Creamos nodo de malla
    GraphicNode* nodoMalla = createNodePR(position, rotation, parent);

    // Creamos malla
    EMesh* malla = new EMesh();
    nodoMalla->setEntity(malla);
    malla->loadMesh(fileName);

    return nodoMalla;
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createPerspectiveCamera(const vec3f position, const vec3f rotation, float fov, float aspect, float near, float far, GraphicNode* parent)
{
    // Invertimos posición y rotación ya que la cámara debe funcionar al revés.
    vec3f pos = vec3f(position.x*-1, position.y*-1, position.z*-1);
    vec3f rot = vec3f(rotation.x*-1, rotation.y*-1, rotation.z*-1);

    // Creamos nodo de cámara
    GraphicNode* nodoCam = createNodePR(pos, rot, parent);

    // Creamos camara
    ECamera* cam = new ECamera();
    cam->setPerspective(fov, aspect, near, far);
    nodoCam->setEntity(cam);

    // Registramos la cámara
    m_cameras.push_back(nodoCam);

    // Activo la cámara recien creada si no hay ninguna activa
    if (m_numActiveCamera == 0)
        setActiveCamera(m_cameras.size());

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


    // Calculamos la matriz Entity::viewMatrix
    calculateTransformMatrix(nodeCam, Entity::viewMatrix, false);
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createLight(const vec3f position, const vec3f rotation, GraphicNode* parent)
{
    // Creamos nodo de luz
    GraphicNode* nodoLuz = createNodePR(position, rotation, parent);
    ELight* luz = new ELight();
    nodoLuz->setEntity(luz);

    // Registramos la luz
    m_lights.push_back(nodoLuz);

    // Activamos luz
    setLightOn(m_lights.size());

    return nodoLuz;
}

/////////////////////
void tag::TAGEngine::setLightOn(const unsigned int light)
{
    // Obtenemos el nodo
    GraphicNode* nodeLuz = m_lights.at(light-1);

    glUniform1i(TAGEngine::m_uLuz0Location, true);

    // Calculamos lMatrix (posición de la luz)
    glm::mat4 lMatrix;
    calculateTransformMatrix(nodeLuz, lMatrix);

    glUniformMatrix4fv(TAGEngine::m_uLMatrixLocation, 1, GL_FALSE, glm::value_ptr(lMatrix));
}

/////////////////////
void tag::TAGEngine::calculateTransformMatrix(const GraphicNode* n, glm::mat4 &matrix, bool premult)
{
    // Inicializamos a identidad
    matrix = glm::mat4();

    // Recorremos hasta root guardando todas las transformaciones.
    std::stack<glm::mat4> pila;
    const GraphicNode* node = n;

    while ( (node=node->getParent()) )
    {
        Entity* entity = node->getEntity();

        // Si hace un cast no válido, devuelve nulo
        if ( ETransform* t = dynamic_cast<ETransform*>(entity) )
            pila.push(t->getMatrix());
    }

    // Aplicamos las transformaciones sacando de la pila
    while (pila.size()>0)
    {
        if (premult)
            matrix = pila.top() * matrix;
        else
            matrix = matrix * pila.top();

        pila.pop();
    }
}

