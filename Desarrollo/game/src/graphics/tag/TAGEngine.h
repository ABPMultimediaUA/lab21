#ifndef TAGENGINE_H
#define TAGENGINE_H

#define MAX_MESSAGE_LINES 4

// Nombre de los attributes
#define A_VERTEXPOSITION    "a_VertexPosition"
#define A_VERTEXNORMAL      "a_VertexNormal"
#define A_TEXTURECOORDS     "a_TextureCoords"

// Nombre de los uniforms
#define U_MVMATRIX              "u_MVMatrix"
#define U_NORMALMATRIX          "u_NormalMatrix"
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVP                   "u_MVP"
#define U_LIGHT_POSITION        "u_Light.position"
#define U_LIGHT_AMBIENT         "u_Light.ambient"
#define U_LIGHT_DIFFUSE         "u_Light.diffuse"
#define U_LIGHT_SPECULAR        "u_Light.specular"
#define U_MATERIAL_HASTEXTURE   "u_MaterialHasTexture"
#define U_MATERIAL_DIFFUSE      "u_MaterialDiffuse"
#define U_MATERIAL_SPECULAR     "u_MaterialSpecular"
#define U_MATERIAL_SHININESS    "u_MaterialShininess"
#define U_HASNORMALTEXTURE      "u_hasNormalTexture"
#define U_NORMALTEXTURE         "u_normalTexture"


#define GLEW_STATIC
#include<GL/glew.h>

#include <glm/glm.hpp>

#include "tag/Types.h"
#include "tag/GraphicNode.h"
#include "tag/EMesh.h"
#include "tag/EAnimation.h"
#include "tag/ETransform.h"


#include "Program.h"
#include "ResourceManager.h"
#include "ResourceMesh.h"

namespace tag
{
    class TAGEngine
    {
        public:
            TAGEngine();

            /// \brief Destructor no virtual, esta clase no debe ser heredada.
            ~TAGEngine();

            /// \brief Inicia el motor.
            /// \details Debe ser llamado antes de cualquier otra funci�n del motor.
            void init(float screenHeight, float screenWidth);

            /// \brief Comprueba que la ventana est� abierta y obtiene los mensajes de la misma.
            /// \details Debe ser llamado antes de dibujar, en cada iteraci�n del bucle.
            /// Obtiene los mensajes de cerrar ventana, maximizar... y los de teclado/rat�n.
            /// \return true si la ventana no ha sido cerrada.
            bool isRunning();

            /// \brief Realiza el dibujado de los nodos.
            /// \details Limpia la ventana openGL, prepara los par�metros de los shaders, las matrices
            /// dibuja los nodos y muestra los fps.
            void draw();

            /// \brief Crea una malla en el arbol.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotaci�n. Crea
            /// el nodo Mesh y le asocia un ResourceMesh con la malla cargada mediante el
            /// ResourceManager.
            /// \param[in] fileName Nombre del fichero que contiene la malla
            /// \param[in] position Posici�n. Crear� un nodo Transform con esos valores
            /// \param[in] rotation Rotaci�n. Crear� un nodo Transform con esos valores
            /// \param[in] textureFileName El nombre del fichero de textura. Si es vacio, no se crea textura.
            /// \param[in] parent Nodo padre. Si es 0 se le asignar� el root.
            /// \return puntero al nodo de la malla creada
            GraphicNode* createMesh(const std::string fileName, const vec3f position, const vec3f rotation, const std::string textureFileName="", GraphicNode* parent=0);

            /// \brief Crea un array de animaciones.
            /// \param[in] numAnimations Numero de animaciones que tendra el array
            /// \param[in] textureFileName Nombre del ficero de textura
            /// \return array de la animaci�n
            EAnimation* createNumAnimations(int numAnimations, const std::string textureFileName = "");

            /// \brief Crea una animacion.
            /// \details Crea una animaci�n en una posici�n del array con el n�mero de mallas que tiene, ley�ndolas
            /// de un archivo al que se le sumar� el n�mero del frame (ej: andando i+1.obj, andando i+2.obj)
            /// \param[in] animations Array que contiene a las animaciones
            /// \param[in] fileName El nombre del archivo sobre el que iterar� para coger todos los obj.
            /// \param[in] numAnimation Posici�n de la animaci�n en el array de animaciones.
            /// \param[in] numFrames N�mero de frames que tendr� la animaci�n. N�mero de mallas.
            void createAnimation(EAnimation* animations, const std::string fileName, int numAnimation, int numFrames, bool loop = true);

            /// \brief Crea el nodo del array de animaciones.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotaci�n. Crea
            /// el nodo nodoAnimation y le asocia el array de animaciones.
            /// \param[in] animations Array que contiene a las animaciones
            /// \param[in] position Posici�n. Crear� un nodo Transform con esos valores
            /// \param[in] rotation Rotaci�n. Crear� un nodo Transform con esos valores
            /// \param[in] parent Nodo padre. Si es 0 se le asignar� el root.
            /// \return puntero al nodo del array de array de mallas.
            GraphicNode* createNodeAnimations(EAnimation* animations, const vec3f position, const vec3f rotation, GraphicNode* parent=0);

            /// \brief Asigna el numero de animacion al nodo.
            /// \details Asigna el numero de animacion al nodo.
            /// \param[in] El nodo.
            /// \param[in] El numero de la animacion en curso.
            void setAnimation(GraphicNode* nodoAnimation, int numAnimation);

            /// \brief Crea una c�mara de perspectiva en el arbol.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotaci�n. Crea
            /// el nodo ECamera y le asigna los parametros de Perspectiva. Si es la primera c�mara que
            /// se crea (si m_numActiveCamera es cero, no hay ninguna activa) llama a setActiveCamera() con la nueva creada.
            /// \param[in] position Posici�n. Crear� un nodo Transform con esos valores
            /// \param[in] rotation Rotaci�n. Crear� un nodo Transform con esos valores
            /// \param[in] fov, aspect, near, far Par�metros para la c�mara de perspectiva.
            /// \param[in] parent Nodo padre. Si es 0 se le asignar� el root.
            /// \return puntero al nodo de la c�mara creada
            GraphicNode* createPerspectiveCamera(const vec3f position, const vec3f rotation, float fov, float aspect, float near, float far, GraphicNode* parent=0);


            /// \brief Establece la c�mara activa. 0 ninguna c�mara activa, 1 primera c�mara...
            /// \details Cuando se establece la c�mara activa se recalculan las transformaciones de la c�mara
            /// y se establece la Entity::viewMatrix.
            void setActiveCamera(const unsigned int activeCamera);

            /// \brief Crea una luz en el �rbol de la escena.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotaci�n. Crea
            /// el nodo ELight. Activa la luz.
            /// \param[in] position Posici�n. Crear� un nodo Transform con esos valores
            /// \param[in] rotation Rotaci�n. Crear� un nodo Transform con esos valores
            /// \param[in] ambient  Intensidad que se asigna en los canales RGB de luz ambiente
            /// \param[in] diffuse  Intensidad que se asigna en los canales RGB de luz difusa
            /// \param[in] specular Intensidad que se asigna en los canales RGB de luz especular
            /// \param[in] parent Nodo padre. Si es 0 se le asignar� el root.
            GraphicNode* createLight(const vec3f position, const vec3f rotation, const vec3f ambient, const vec3f diffuse, const vec3f specular, GraphicNode* parent=0);

            /// \brief Activa o desactiva una luz.
            /// \param[in] Posici�n en el array de luces de la luz a activar o desactivar.
            void setLightOn(const unsigned int light);

            /// \brief Funci�n para calcular la posici�n y rotaci�n de la c�mara o de la luz
            /// \details Es llamada por setActiveCamera y setLightOn. Busca en los nodos superiores
            /// los nodos de transformaci�n, los guarda en una pila para luego aplicarlos de manera
            /// inversa a como se han obtenido.
            /// \param[in] nodo luz/c�mara.
            /// \param[in] matriz de posici�n de luz o c�mara (view)
            /// \param[in] premult Indica si hacemos premultiplicaci�n o no
            void calculateTransformMatrix(const GraphicNode* node, glm::mat4 &matrix);


            /// \brief Mueve un nodo movement posiciones respecto a su actual posici�n.
            /// \details Busca el nodo padre. En un arbol bien construido el nodo padre del nodo a
            /// mover debe tener una entidad de transformaci�n de posici�n.
            /// \param[in] node Nodo que se quiere mover
            /// \param[in] movement que se quiere a�adir al que ya tiene el nodo
            void moveNodeEntity(GraphicNode* node, const vec3f movement);
            void setPositionNodeEntity(GraphicNode* node, const vec3f movement);


            /// \brief Rota un nodo rotation grados respecto a su actual rotaci�n.
            /// \details Busca el nodo padre. En un arbol bien construido el nodo
            /// padre del padre del nodo a mover debe tener una entidad de
            /// transformaci�n de rotaci�n.
            /// \param[in] node Nodo que se quiere mover
            /// \param[in] rotation que se quiere a�adir al que ya tiene el nodo
            void rotateNodeEntity(GraphicNode* node, const vec3f rotation);
            void setRotationNodeEntity(GraphicNode* node, const vec3f rotation);


            /// \brief Set the position of the node, and calculate rotation from position to target
            /// \param[in] node to move and rotate
            /// \param[in] position of the node
            /// \param[in] target to calculate the rotation from position
            void nodeLookAtTarget(GraphicNode* node, const vec3f position, const vec3f target);

            // TODO nodeLookAtScreenCoords
            void nodeLookAtScreenCoords(GraphicNode* node, const vec3f position, const vec3f screenCoords);

            /// \brief Borra un nodo, y sus nodos padres transformacion.
            /// \details Busca todos los padres que sean transformaci�n, hasta llegar a uno que
            /// no lo sea, y borra ese nodo. El destructor del nodo se encarga de borrar los
            /// hijos. Del primer nodo borrado, se quita de la lista de hijos de su parent.
            /// Realiza los deletes pertinentes.
            void deleteNode(GraphicNode* node);

            // Handles de los attributes y uniforms
            static int _aVertexPositionLocation;
            static int _aVertexNormalLocation;
            static int _aTextureCoordsLocation;
            static int _uMVMatrixLocation;
            static int _uNormalMatrixLocation;
            static int _uProjectionMatrixLocation;
            static int _uMVPLocation;
            static int _uLightPositionLocation;
            static int _uLightAmbientLocation;
            static int _uLightDiffuseLocation;
            static int _uLightSpecularLocation;
            static int _uMaterialHasTextureLocation;
            static int _uMaterialDiffuseLocation;
            static int _uMaterialSpecularLocation;
            static int _uMaterialShininessLocation;
            static int _uHasNormalTextureLocation;
            static int _uNormalTextureLocation;

            static float _screenHeight;
            static float _screenWidth;

        private:
            enum ENodeTransformOrder { eNodeRotation=2, eNodeTranslation=1 };

            Program*                    m_shaderProgram;

            GraphicNode                 m_rootNode;
            std::vector<GraphicNode*>   m_lights;
            std::vector<GraphicNode*>   m_cameras;
            unsigned int                m_numActiveCamera;

            glm::mat4 m_projectionMatrix; // Almacena la matriz de proyecci�n

            void renderElements();

            GraphicNode* createNodeTransform(GraphicNode* parent);
            GraphicNode* createNodeRotation(const vec3f rotation, GraphicNode* parent);
            GraphicNode* createNodeTranslation(const vec3f position, GraphicNode* parent);
            GraphicNode* createNodePR(const vec3f position, const vec3f rotation, GraphicNode* parent);
            void calculateViewMatrix();
            glm::vec4 getVectorFromMatrix(glm::mat4 matrix);
            glm::vec3 fromTagVec3fToGlmVec3(vec3f tagv);

            /// \brief Obtiene la endiad del deep nodo padre del nodo pasado, lanzando excepciones si el �rbol est� mal
            /// formado o lo que devuelve no es una entidad de transformaci�n
            ETransform* getTransformNode(GraphicNode* node, ENodeTransformOrder deep);
    };
}

#endif // TAGENGINE_H
