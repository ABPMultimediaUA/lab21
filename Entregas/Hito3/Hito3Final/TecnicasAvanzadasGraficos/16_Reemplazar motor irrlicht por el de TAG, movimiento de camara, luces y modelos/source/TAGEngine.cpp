#include "tag/TAGEngine.h"

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "Shader.h"
#include "tag/Entity.h"
#include "tag/ResourceMesh.h"
#include "tag/ECamera.h"
#include "tag/ELight.h"
#include "tag/ETransform.h"
#include "tag/EMesh.h"
#include "tag/EAnimation.h"
#include "tag/TAGError.h"

#include "dwVectors.h"

int tag::TAGEngine::_aVertexPositionLocation;
int tag::TAGEngine::_aVertexNormalLocation;
int tag::TAGEngine::_aTextureCoordsLocation;
int tag::TAGEngine::_uMVMatrixLocation;
int tag::TAGEngine::_uNormalMatrixLocation;
int tag::TAGEngine::_uProjectionMatrixLocation;
int tag::TAGEngine::_uMVPLocation;
int tag::TAGEngine::_uLightPositionLocation;
int tag::TAGEngine::_uLightAmbientLocation;
int tag::TAGEngine::_uLightDiffuseLocation;
int tag::TAGEngine::_uLightSpecularLocation;
int tag::TAGEngine::_uMaterialHasTextureLocation;
int tag::TAGEngine::_uMaterialDiffuseLocation;
int tag::TAGEngine::_uMaterialSpecularLocation;
int tag::TAGEngine::_uMaterialShininessLocation;
int tag::TAGEngine::_uHasNormalTextureLocation;
int tag::TAGEngine::_uNormalTextureLocation;


float tag::TAGEngine::_screenHeight;
float tag::TAGEngine::_screenWidth;


tag::TAGEngine::TAGEngine() :
    m_shaderProgram(0),
    m_rootNode(),
    m_lights(),
    m_cameras(),
    m_numActiveCamera(0)
{
}

tag::TAGEngine::~TAGEngine()
{
    if (m_shaderProgram)
    {
        delete m_shaderProgram;
        m_shaderProgram = 0;
    }
}

/////////////////////
void tag::TAGEngine::init(float screenHeight, float screenWidth)
{
    TAGEngine::_screenHeight = screenHeight;
    TAGEngine::_screenWidth = screenWidth;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(100.0);

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);

    // Inicializaci�n de GLEW
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // Carga de los Shaders
    Shader shader;
    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    shaders.push_back(shader.LoadShader("shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));

    if (!m_shaderProgram)
        m_shaderProgram = new Program(shaders);
    glUseProgram(m_shaderProgram->ReturnProgramID());

    // Attributes
    TAGEngine::_aVertexPositionLocation = m_shaderProgram->attrib(A_VERTEXPOSITION);
    TAGEngine::_aVertexNormalLocation   = m_shaderProgram->attrib(A_VERTEXNORMAL);
    TAGEngine::_aTextureCoordsLocation  = m_shaderProgram->attrib(A_TEXTURECOORDS);

    // Uniforms
    TAGEngine::_uMVMatrixLocation           = m_shaderProgram->uniform(U_MVMATRIX);
    TAGEngine::_uNormalMatrixLocation       = m_shaderProgram->uniform(U_NORMALMATRIX);
    TAGEngine::_uMVPLocation                = m_shaderProgram->uniform(U_MVP);
    TAGEngine::_uLightPositionLocation      = m_shaderProgram->uniform(U_LIGHT_POSITION);
    TAGEngine::_uLightAmbientLocation       = m_shaderProgram->uniform(U_LIGHT_AMBIENT);
    TAGEngine::_uLightDiffuseLocation       = m_shaderProgram->uniform(U_LIGHT_DIFFUSE);
    TAGEngine::_uLightSpecularLocation      = m_shaderProgram->uniform(U_LIGHT_SPECULAR);
    TAGEngine::_uMaterialHasTextureLocation = m_shaderProgram->uniform(U_MATERIAL_HASTEXTURE);
    TAGEngine::_uMaterialDiffuseLocation    = m_shaderProgram->uniform(U_MATERIAL_DIFFUSE);
    TAGEngine::_uMaterialSpecularLocation   = m_shaderProgram->uniform(U_MATERIAL_SPECULAR);
    TAGEngine::_uMaterialShininessLocation  = m_shaderProgram->uniform(U_MATERIAL_SHININESS);
    TAGEngine::_uHasNormalTextureLocation   = m_shaderProgram->uniform(U_HASNORMALTEXTURE);
    TAGEngine::_uNormalTextureLocation      = m_shaderProgram->uniform(U_NORMALTEXTURE);

    glUseProgram(0);
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

    if (!m_rootNode.isEmptyNode())
    {
        glUseProgram(m_shaderProgram->ReturnProgramID());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Habilitamos el paso de attributes
        glEnableVertexAttribArray(TAGEngine::_aVertexPositionLocation);
        glEnableVertexAttribArray(TAGEngine::_aVertexNormalLocation);
        glEnableVertexAttribArray(TAGEngine::_aTextureCoordsLocation);

        // C�lculo de la vista (c�mara)
        calculateViewMatrix();

        // Dibujar
        renderElements();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisableVertexAttribArray(TAGEngine::_aVertexPositionLocation);
        glDisableVertexAttribArray(TAGEngine::_aVertexNormalLocation);
        glDisableVertexAttribArray(TAGEngine::_aTextureCoordsLocation);

        glUseProgram(0);
    }
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

    // Creamos nodo de Rotaci�n
    GraphicNode* nodoRotacion = createNodeRotation(rotation, parent);

    // Creamos nodo de traslaci�n (posici�n)
    GraphicNode* nodoTraslacion = createNodePosition(position, nodoRotacion);

    // Cremamos nodo final
    GraphicNode* nodo = new GraphicNode();
    nodoTraslacion->addChild(nodo);

    return nodo;
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createMesh(const std::string fileName, const vec3f position, const vec3f rotation, const std::string textureFileName, GraphicNode* parent)
{
    // Debemos de volver a poner el useProgram
    // Si entre que se inicia el motor y se cargan los modelos
    // se dibuja sfml, no carga bien si no hacemos esto.
    glUseProgram(m_shaderProgram->ReturnProgramID());

    // Creamos nodo de malla
    GraphicNode* nodoMalla = createNodePR(position, rotation, parent);

    // Creamos malla
    EMesh* malla = new EMesh();
    nodoMalla->setEntity(malla);
    malla->loadMesh(fileName);

    // Cargamos textura
    if (textureFileName != "")
        malla->loadTexture(textureFileName);

    return nodoMalla;
}

////////////////////////////
tag::EAnimation* tag::TAGEngine::createNumAnimations(int numAnimations)
{
    // Creamos malla
    EAnimation* animations = new EAnimation();
    animations->createNumAnimations(numAnimations);//num animaciones

    return animations;
}
////////////////////////////
tag::EAnimation* tag::TAGEngine::createAnimation(EAnimation* animations, const std::string fileName, int numAnimation, int numFrames)
{
    animations->createAnimation(numAnimation,numFrames, fileName);//creamos la animacion con sus frames y sus mallas
    return animations;//la devolvemos
}

/////////////////////////////
tag::GraphicNode* tag::TAGEngine::createNodeAnimations(EAnimation* animations, const vec3f position, const vec3f rotation, GraphicNode* parent)
{
    // Creamos nodo de animation
    GraphicNode* nodoAnimation = createNodePR(position, rotation, parent);
    nodoAnimation->setEntity(animations);//asignamos la animacion al nodo
    return nodoAnimation;

}
//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createPerspectiveCamera(const vec3f position, const vec3f rotation, float fov, float aspect, float near, float far, GraphicNode* parent)
{
    // Creamos nodo de c�mara
    GraphicNode* nodoCam = createNodePR(position, rotation, parent);

    // Creamos camara
    ECamera* cam = new ECamera();
    cam->setPerspective(fov, aspect, near, far);
    nodoCam->setEntity(cam);

    // Registramos la c�mara
    m_cameras.push_back(nodoCam);

    // Activo la c�mara recien creada si no hay ninguna activa
    if (m_numActiveCamera == 0)
        setActiveCamera(m_cameras.size());

    return nodoCam;
}

/////////////////////
void tag::TAGEngine::setActiveCamera(const unsigned int activeCamera)
{
    if (activeCamera > m_cameras.size())
        throw std::runtime_error("La c�mara que se est� pasando en setActiveCamera no es v�lida.");

    m_numActiveCamera = activeCamera;
}

/////////////////////
void tag::TAGEngine::calculateViewMatrix()
{
    // Obtenemos el nodo
    GraphicNode* nodeCam = m_cameras.at(m_numActiveCamera-1);

    // Estableciendo la matriz de proyecci�n perspectiva
    Entity::projectionMatrix = static_cast<ECamera*>(nodeCam->getEntity())->getProjectionMatrix();

    // Calculamos la matriz Entity::viewMatrix
    calculateTransformMatrix(nodeCam, Entity::viewMatrix);

    // Invertimos la matriz
    Entity::viewMatrix = glm::inverse(Entity::viewMatrix);
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createLight(const vec3f position, const vec3f rotation, const vec3f ambient, const vec3f diffuse, const vec3f specular, GraphicNode* parent)
{
    // Creamos nodo de luz
    GraphicNode* nodoLuz = createNodePR(position, rotation, parent);
    ELight* luz = new ELight();
    luz->setAmbientIntensity(ambient);
    luz->setDiffuseIntensity(diffuse);
    luz->setSpecularIntensity(specular);

    nodoLuz->setEntity(luz);

    // Registramos la luz
    m_lights.push_back(nodoLuz);

    // Activamos luz
    setLightOn(m_lights.size());

    return nodoLuz;
}

//////////////////////////
glm::vec4 tag::TAGEngine::getVectorFromMatrix(glm::mat4 matrix)
{
    glm::vec4 v;
    for (uint8_t i=0; i<4; i++)
        v[i] = matrix[3][i];
    return v;
}

glm::vec3 tag::TAGEngine::fromTagVec3fToGlmVec3(vec3f tagv)
{
    return glm::vec3(tagv.x, tagv.y, tagv.z);
}

/////////////////////
void tag::TAGEngine::setLightOn(const unsigned int light)
{
    // Obtenemos el nodo
    GraphicNode* nodeLuz = m_lights.at(light-1);
    ELight* luz = static_cast<ELight*>(nodeLuz->getEntity());

    // Calculamos lMatrix (posici�n de la luz)
    glm::mat4 lMatrix;
    calculateTransformMatrix(nodeLuz, lMatrix);
    glm::vec4 pos = getVectorFromMatrix(lMatrix);
    glUniform4fv(TAGEngine::_uLightPositionLocation, 1, &pos[0]);

    vec3f intensity = luz->getAmbientIntensity();
    glUniform3f(TAGEngine::_uLightAmbientLocation, intensity.x, intensity.y, intensity.z);

    intensity = luz->getDiffuseIntensity();
    glUniform3f(TAGEngine::_uLightDiffuseLocation, intensity.x, intensity.y, intensity.z);

    intensity = luz->getSpecularIntensity();
    glUniform3f(TAGEngine::_uLightSpecularLocation, intensity.x, intensity.y, intensity.z);
}

/////////////////////
void tag::TAGEngine::calculateTransformMatrix(const GraphicNode* n, glm::mat4 &matrix)
{
    // Inicializamos a identidad
    matrix = glm::mat4();

    // Recorremos hasta root guardando todas las transformaciones.
    std::stack<glm::mat4> pila;
    const GraphicNode* node = n;

    while ( (node=node->getParent()) )
    {
        Entity* entity = node->getEntity();

        // Si hace un cast no v�lido, devuelve nulo
        if ( ETransform* t = dynamic_cast<ETransform*>(entity) )
            pila.push(t->getMatrix());
    }

    // Aplicamos las transformaciones sacando de la pila
    while (pila.size()>0)
    {
        matrix = pila.top() * matrix;
        pila.pop();
    }
}

/////////////////////////////////
tag::ETransform* tag::TAGEngine::getTransformNode(GraphicNode* node, uint8_t deep)
{
    if (node)
    {
        // Buscamos la profundidad de padre que nos pasan por par�metro
        GraphicNode* n = node;
        for(uint8_t i=0; i<deep; i++)
        {
            n = n->getParent();
            if (!n)
                throw std::runtime_error("getTransformNode: el nodo padre est� vacio");
        }

        // Buscar que el nodo padre encontrado sea una transformacion
        ETransform* t = dynamic_cast<ETransform*>(n->getEntity());
        if (t)
            return t;
        else
            throw std::runtime_error("getTransformNode Error en la forma del arbol. El nodo padre no es de transformaci�n.");
    }
    else
        throw std::runtime_error("getTransformNode: el nodo pasado por par�metro est� vacio");
}


/////////////////////
void tag::TAGEngine::moveNodeEntity(GraphicNode* node, const vec3f movement)
{
    // Pasamos 1, ya que el nodo padre debe ser una transformaci�n de traslaci�n
    getTransformNode(node, 1)->translate(movement);
}

/////////////////////
void tag::TAGEngine::setPositionNodeEntity(GraphicNode* node, const vec3f movement)
{
    // Pasamos 1, ya que el nodo padre debe ser una transformaci�n de traslaci�n
    ETransform* t = getTransformNode(node, 1);
    t->identity();  // Ponemos a cero
    t->translate(movement);  // Movemos a posici�n dada
}

/////////////////////
void tag::TAGEngine::rotateNodeEntity(GraphicNode* node, const vec3f rotation)
{
    // Pasamos 2, ya que el nodo padre del padre debe ser una transformaci�n de rotaci�n
    getTransformNode(node, 2)->rotate(rotation);
}

/////////////////////
void tag::TAGEngine::setRotationNodeEntity(GraphicNode* node, const vec3f rotation)
{
    // Pasamos 2, ya que el nodo padre del padre debe ser una transformaci�n de rotaci�n
    ETransform* t = getTransformNode(node, 2);
    t->identity();  // Ponemos a cero
    t->rotate(rotation);  // Rotamos a rotaci�n dada
}

/////////////////////
void tag::TAGEngine::nodeLookAtTarget(GraphicNode* node, const vec3f position, const vec3f target)
{
    setPositionNodeEntity(node, position);

    float anguloX=0;
    float anguloY=0;

    vec3f positionToTarget(target.x - position.x,  target.y - position.y,  target.z - position.z);

    vec2f normalized2d;

    // Calculamos angulo X, utilizando y z
    normalized2d = dwu::normalizeVector(vec2f(positionToTarget.y, positionToTarget.z));
    anguloX = dwu::calculateDegrees(normalized2d, vec2f(0,-1));
    if (target.y<position.y)
        anguloX *= (-1);

    // Calculamos angulo Y, utilizando x z
    normalized2d = dwu::normalizeVector(vec2f(positionToTarget.x, positionToTarget.z));
    anguloY = dwu::calculateDegrees(normalized2d, vec2f(0,-1));
    if (target.x>position.x)
        anguloY *= (-1);


    setRotationNodeEntity(node, vec3f(anguloX, anguloY, 0));
}

/////////////////////
void tag::TAGEngine::deleteNode(GraphicNode* node)
{
    // Buscamos el nodo con transformaci�n m�s lejano hacia arriba
    GraphicNode* nodeTransform;
    GraphicNode* parent = node->getParent();
    while (dynamic_cast<ETransform*>(parent->getEntity()))   // mientras el parent tenga de entidad un ETransform
    {
        nodeTransform = parent;
        parent = parent->getParent();
    }

    // Una vez tenemos el primer nodo transformaci�n, borramos ese
    nodeTransform->getParent()->removeChild(nodeTransform);   // Lo quitamos del padre
    delete nodeTransform;   // el delete se encarga de borrar los hijos
}


