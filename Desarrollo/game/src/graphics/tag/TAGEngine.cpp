#include "tag/TAGEngine.h"

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <sstream>

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
#define M_PI		3.14159265358979323846

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
int tag::TAGEngine::_uModelMatrixLocation;

int tag::TAGEngine::_uShadowTextureLocation;
int tag::TAGEngine::_uLightSpaceMatrixLocation;

int tag::TAGEngine::_aShadowVertexPositionLocation;
int tag::TAGEngine::_uShadowMVPLocation;
int tag::TAGEngine::_uHasShadowsLocation;

GLuint tag::TAGEngine::_shadowHeight = 512;
GLuint tag::TAGEngine::_shadowWidth = 512;

float tag::TAGEngine::_screenHeight;
float tag::TAGEngine::_screenWidth;

tag::TAGEngine::TAGEngine() :
    m_shaderProgram(0),
    m_shadowProgram(0),
    m_rootNode(),
    m_lights(),
    m_cameras(),
    m_numActiveCamera(0),
    m_depthMap(0)
{
}

tag::TAGEngine::~TAGEngine()
{
    if (m_shaderProgram)
    {
        delete m_shaderProgram;
        m_shaderProgram = 0;
    }

    if (m_shadowProgram)
    {
        delete m_shadowProgram;
        m_shadowProgram = 0;
    }
}

/////////////////////
void tag::TAGEngine::init(float screenHeight, float screenWidth, uint16_t shadowSize)
{
    configure(screenHeight, screenWidth, shadowSize);

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
    TAGEngine::_uModelMatrixLocation        = m_shaderProgram->uniform(U_MODELMATRIX);
    TAGEngine::_uShadowTextureLocation      = m_shaderProgram->uniform(U_SHADOWTEXTURE);
    TAGEngine::_uLightSpaceMatrixLocation   = m_shaderProgram->uniform(U_LIGHT_SPACE_MATRIX);
    TAGEngine::_uHasShadowsLocation         = m_shaderProgram->uniform(U_HASSHADOWS);

    glUniform1i(TAGEngine::_uMaterialDiffuseLocation,   Entity::_diffuseTextureIndex);
    glUniform1i(TAGEngine::_uMaterialSpecularLocation,  Entity::_specularTextureIndex);
    glUniform1i(TAGEngine::_uNormalTextureLocation,     Entity::_normalTextureIndex);

    glUniform1i(TAGEngine::_uHasShadowsLocation, m_renderShadows);

    if (m_renderShadows)
    {
        // Shaders para shadows
        shaders.clear();
        shaders.push_back(shader.LoadShader("shaders/shadowVertexShader.glsl", GL_VERTEX_SHADER));
        shaders.push_back(shader.LoadShader("shaders/shadowFragmentShader.glsl", GL_FRAGMENT_SHADER));

        if (!m_shadowProgram)
            m_shadowProgram = new Program(shaders);

        glUseProgram(m_shadowProgram->ReturnProgramID());
        TAGEngine::_aShadowVertexPositionLocation   = m_shadowProgram->attrib(A_VERTEXPOSITION);
        TAGEngine::_uShadowMVPLocation              = m_shadowProgram->uniform(U_MVP);


        prepareShadows();
    }

    glUseProgram(0);
}

/////////////////////
void tag::TAGEngine::configure(float screenHeight, float screenWidth, uint16_t shadowSize)
{
    TAGEngine::_screenHeight    = screenHeight;
    TAGEngine::_screenWidth     = screenWidth;
    TAGEngine::_shadowHeight    = shadowSize;
    TAGEngine::_shadowWidth     = shadowSize;
    m_renderShadows             = !(shadowSize == 0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Inicialización de GLEW
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    if (m_shaderProgram)
    {   // Si ya se ha inicializado previamente
        glUseProgram(m_shaderProgram->ReturnProgramID());
        glUniform1i(TAGEngine::_uHasShadowsLocation, m_renderShadows);
        glUseProgram(0);
        if (m_renderShadows)
            prepareShadows();
    }
}

/////////////////////
bool tag::TAGEngine::isRunning()
{
    return true;
}

/////////////////////
void tag::TAGEngine::draw(float x, float z)
{
    glm::mat4 rotateMatrix;
    glm::vec3 positionMatrix;

    if (!m_rootNode.isEmptyNode())
    {
        // Cálculo de la vista (cámara)
        calculateViewMatrix();

        if (m_renderShadows)
            calculateShadows(x, z);

        glUseProgram(m_shaderProgram->ReturnProgramID());
        glViewport(0, 0, TAGEngine::_screenWidth, TAGEngine::_screenHeight);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Habilitamos el paso de attributes
        glEnableVertexAttribArray(TAGEngine::_aVertexPositionLocation);
        glEnableVertexAttribArray(TAGEngine::_aVertexNormalLocation);
        glEnableVertexAttribArray(TAGEngine::_aTextureCoordsLocation);

        glUniformMatrix4fv(TAGEngine::_uLightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(Entity::lightSpaceMatrix));

        // Textura de shadows
        if (m_renderShadows)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_depthMap);
            glUniform1i(TAGEngine::_uShadowTextureLocation, 0);
        }

        // Dibujar
        Entity::isPreDraw = false;
        renderElements();

        // Desactivamos textura de shadows, aún no teniendo
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableVertexAttribArray(TAGEngine::_aVertexPositionLocation);
        glDisableVertexAttribArray(TAGEngine::_aVertexNormalLocation);
        glDisableVertexAttribArray(TAGEngine::_aTextureCoordsLocation);

        glUseProgram(0);
    }
}

/////////////////////
void tag::TAGEngine::prepareShadows()
{
    glViewport(0, 0, TAGEngine::_shadowWidth, TAGEngine::_shadowHeight);

    // Si están creados los borro
    if (m_depthMap)
    {
        glDeleteTextures(1, &m_depthMap);
        glDeleteFramebuffers(1, &m_depthMapFBO);
    }

    glGenTextures(1, &m_depthMap);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, TAGEngine::_shadowWidth, TAGEngine::_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glGenFramebuffers(1, &m_depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void tag::TAGEngine::configureShadowLight(const vec3f position)
{
    GLfloat near_plane  = 0.1;
    GLfloat far_plane   = 400.0;
    float   ortho       = 400.0;

    m_lightPosition   = position;
    m_lightProjection = glm::ortho(-ortho, ortho, -ortho, ortho, near_plane, far_plane);
}

/////////////////////
void tag::TAGEngine::calculateShadows(float x, float z)
{
    glUseProgram(m_shadowProgram->ReturnProgramID());

    glm::mat4 lightView;
    lightView = glm::lookAt(glm::vec3(x+m_lightPosition.x, m_lightPosition.y, z+m_lightPosition.z), glm::vec3(x, 0, z), glm::vec3(0, 1, 0));
    Entity::lightSpaceMatrix = m_lightProjection * lightView;

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(TAGEngine::_aShadowVertexPositionLocation);

    glBindTexture(GL_TEXTURE_2D, m_depthMap);

    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
    glViewport(0, 0, TAGEngine::_shadowWidth, TAGEngine::_shadowHeight);

    glClear(GL_DEPTH_BUFFER_BIT);

    // Dibujar
    Entity::isPreDraw = true;
    glCullFace(GL_FRONT);
    m_rootNode.draw();
    glCullFace(GL_BACK);

    // Limpiar estados opengl
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(TAGEngine::_aShadowVertexPositionLocation);
    glBindTexture(GL_TEXTURE_2D, 0);
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
tag::GraphicNode* tag::TAGEngine::createNodeTranslation(const vec3f position, GraphicNode* parent)
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
    GraphicNode* nodoTraslacion = createNodeTranslation(position, nodoRotacion);

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
tag::EAnimation* tag::TAGEngine::createNumAnimations(int numAnimations, const std::string textureFileName)
{
    // Creamos malla
    EAnimation* animations = new EAnimation();
    animations->createNumAnimations(numAnimations);//num animaciones

    // Cargamos textura
    if (textureFileName != "")
        animations->loadTexture(textureFileName);

    return animations;
}

////////////////////////////
void tag::TAGEngine::createAnimation(EAnimation* animations, const std::string fileName, int numAnimation, int numFrames, bool loop)
{
    animations->createAnimation(numAnimation,numFrames, fileName, loop);//creamos la animacion con sus frames y sus mallas
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

void tag::TAGEngine::setAnimation(GraphicNode* nodoAnimation, int numAnimation)
{
    EAnimation* animation = nodoAnimation->getAnimation();
    if (animation)
        animation->setActiveAnimation(numAnimation);
}

////////////////////////////
tag::GraphicNode* tag::TAGEngine::createPerspectiveCamera(const vec3f position, const vec3f rotation, float fov, float aspect, float near, float far, GraphicNode* parent)
{
    // Creamos nodo de cámara
    GraphicNode* nodoCam = createNodePR(position, rotation, parent);

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
    if (activeCamera > m_cameras.size())
        throw std::runtime_error("La cámara que se está pasando en setActiveCamera no es válida.");

    m_numActiveCamera = activeCamera;
}

/////////////////////
void tag::TAGEngine::calculateViewMatrix()
{
    // Obtenemos el nodo
    GraphicNode* nodeCam = m_cameras.at(m_numActiveCamera-1);

    // Estableciendo la matriz de proyección perspectiva
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

    glUseProgram(m_shaderProgram->ReturnProgramID());

    // Calculamos lMatrix (posición de la luz)
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

        // Si hace un cast no válido, devuelve nulo
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
tag::ETransform* tag::TAGEngine::getTransformNode(GraphicNode* node, ENodeTransformOrder deep)
{
    if (node)
    {
        // Buscamos la profundidad de padre que nos pasan por parámetro
        GraphicNode* n = node;
        for(uint8_t i=0; i<deep; i++)
        {
            n = n->getParent();
            if (!n)
                throw std::runtime_error("getTransformNode: el nodo padre está vacio");
        }

        // Buscar que el nodo padre encontrado sea una transformacion
        ETransform* t = dynamic_cast<ETransform*>(n->getEntity());
        if (t)
            return t;
        else
            throw std::runtime_error("getTransformNode Error en la forma del arbol. El nodo padre no es de transformación.");
    }
    else
        throw std::runtime_error("getTransformNode: el nodo pasado por parámetro está vacio");
}


/////////////////////
void tag::TAGEngine::moveNodeEntity(GraphicNode* node, const vec3f movement)
{
    // Pasamos 1, ya que el nodo padre debe ser una transformación de traslación
    getTransformNode(node, eNodeTranslation)->translate(movement);
}

/////////////////////
void tag::TAGEngine::setPositionNodeEntity(GraphicNode* node, const vec3f movement)
{
    // Pasamos 1, ya que el nodo padre debe ser una transformación de traslación
    ETransform* t = getTransformNode(node, eNodeTranslation);
    t->identity();  // Ponemos a cero
    t->translate(movement);  // Movemos a posición dada
}

/////////////////////
void tag::TAGEngine::rotateNodeEntity(GraphicNode* node, const vec3f rotation)
{
    // Pasamos 2, ya que el nodo padre del padre debe ser una transformación de rotación
    getTransformNode(node, eNodeRotation)->rotate(rotation);
}

/////////////////////
void tag::TAGEngine::setRotationNodeEntity(GraphicNode* node, const vec3f rotation)
{
    // Pasamos 2, ya que el nodo padre del padre debe ser una transformación de rotación
    ETransform* t = getTransformNode(node, eNodeRotation);
    t->identity();  // Ponemos a cero
    t->rotate(rotation);  // Rotamos a rotación dada
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
float tag::TAGEngine::angleToScreenCoords(const vec3f position, const vec3f screenCoords)
{
    calculateViewMatrix();
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, TAGEngine::_screenWidth, TAGEngine::_screenHeight);

    GLfloat depthZ;
    glReadPixels(screenCoords.x, screenCoords.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthZ);

    glm::vec3 unCoords = glm::unProject(
            glm::vec3(screenCoords.x, TAGEngine::_screenHeight-screenCoords.y-1.0, 0.9998),
            Entity::viewMatrix,
            Entity::projectionMatrix,
            viewport);

    float x = unCoords.x-position.x;
    float z = unCoords.z-position.z;

    float modulo = sqrt(pow(x,2) + pow(z,2));
    float normX = x/modulo;
    float angulo = acos(normX) * (180/M_PI);

    if (unCoords.z > position.z)
        angulo = -angulo;

    return angulo;
}

/////////////////////
void tag::TAGEngine::deleteNode(GraphicNode* node)
{
    // Buscamos el nodo con transformación más lejano hacia arriba
    GraphicNode* parent = node->getParent();
    GraphicNode* nodeTransform = node;  // Para los que no tienen nodo transform
    while (dynamic_cast<ETransform*>(parent->getEntity()))   // mientras el parent tenga de entidad un ETransform
    {
        nodeTransform = parent;
        parent = parent->getParent();
    }

    // Una vez tenemos el primer nodo transformación, borramos ese
    nodeTransform->getParent()->removeChild(nodeTransform);   // Lo quitamos del padre
    delete nodeTransform;   // el delete se encarga de borrar los hijos
}

/////////////////////
void tag::TAGEngine::changeLightIntensity(uint8_t lightIndex, const vec3f ambient, const vec3f diffuse, const vec3f specular)
{
    if (lightIndex<=m_lights.size())
    {
        ELight* luz = static_cast<ELight*>(m_lights.at(lightIndex-1)->getEntity());

        luz->setAmbientIntensity(ambient);
        luz->setDiffuseIntensity(diffuse);
        luz->setSpecularIntensity(specular);

        glUseProgram(m_shaderProgram->ReturnProgramID());

        vec3f intensity = luz->getAmbientIntensity();
        glUniform3f(TAGEngine::_uLightAmbientLocation, intensity.x, intensity.y, intensity.z);

        intensity = luz->getDiffuseIntensity();
        glUniform3f(TAGEngine::_uLightDiffuseLocation, intensity.x, intensity.y, intensity.z);

        intensity = luz->getSpecularIntensity();
        glUniform3f(TAGEngine::_uLightSpecularLocation, intensity.x, intensity.y, intensity.z);
    }
}

//////////////////////////////////
tag::GraphicNode* tag::TAGEngine::createEmptyNode(GraphicNode* parent)
{
    // Si no especificamos padre, usamos el root. 0 es el valor por defecto
    if (parent==0)
        parent = &m_rootNode;

    GraphicNode* nodo = new GraphicNode();
    parent->addChild(nodo);

    return nodo;
}

