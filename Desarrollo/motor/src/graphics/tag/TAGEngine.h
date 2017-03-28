#ifndef TAGENGINE_H
#define TAGENGINE_H

#define MAX_MESSAGE_LINES 4

// Nombre de los attributes
#define A_POSITION      "a_Position"
#define A_NORMAL        "a_Normal"
#define A_TEXTURECOORDS "a_TextureCoords"

// Nombre de los uniforms
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_LMATRIX               "u_LMatrix"
#define U_COLOR                 "u_Color"
#define U_LUZ0                  "u_Luz0"
#define U_TEXTURESAMPLER        "u_TextureSampler"


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

            /// \brief Crea una malla en el arbol.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotaci�n. Crea
            /// el nodo Animation y le asocia un ResourceMesh con la malla cargada mediante el
            /// ResourceManager.
            /// \param[in] fileName Nombre del fichero que contiene la malla
            /// \param[in] position Posici�n. Crear� un nodo Transform con esos valores
            /// \param[in] rotation Rotaci�n. Crear� un nodo Transform con esos valores
            /// \param[in] parent Nodo padre. Si es 0 se le asignar� el root.
            /// \return puntero al nodo de la malla creada
            GraphicNode* createAnimation(const std::string fileName, const vec3f position, const vec3f rotation, GraphicNode* parent=0);

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
            /// \param[in] parent Nodo padre. Si es 0 se le asignar� el root.
            GraphicNode* createLight(const vec3f position, const vec3f rotation, GraphicNode* parent=0);

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


            /// \brief Borra un nodo, y sus nodos padres transformacion
            /// \details Busca todos los padres que sean transformaci�n, hasta llegar a uno que
            /// no lo sea, y borra ese nodo. El destructor del nodo se encarga de borrar los
            /// hijos. Del primer nodo borrado, se quita de la lista de hijos de su parent.
            void deleteNode(GraphicNode* node);


            // Handles de los attributes y uniforms
            static int _aPositionLocation;
            static int _aNormalLocation;
            static int _aTextureCoordsLocation;
            static int _uProjectionMatrixLocation;
            static int _uMVMatrixLocation;
            static int _uLMatrixLocation;
            static int _uColorLocation;
            static int _uLuz0Location;
            static int _uTextureSamplerLocation;

            static float _screenHeight;
            static float _screenWidth;

        private:
            Program*                    m_shaderProgram;

            GraphicNode                 m_rootNode;
            std::vector<GraphicNode*>   m_lights;
            std::vector<GraphicNode*>   m_cameras;
            unsigned int                m_numActiveCamera;

            glm::mat4 m_projectionMatrix; // Almacena la matriz de proyecci�n

            void renderElements();

            GraphicNode* createNodeTransform(GraphicNode* parent);
            GraphicNode* createNodeRotation(const vec3f rotation, GraphicNode* parent);
            GraphicNode* createNodePosition(const vec3f position, GraphicNode* parent);
            GraphicNode* createNodePR(const vec3f position, const vec3f rotation, GraphicNode* parent);
            void calculateViewMatrix();

            /// \brief Obtiene la endiad del deep nodo padre del nodo pasado, lanzando excepciones si el �rbol est� mal
            /// formado o lo que devuelve no es una entidad de transformaci�n
            ETransform* getTransformNode(GraphicNode* node, uint8_t deep);

            /// \brief Returns the normalized vector of v
            vec2f normalizeVector(const vec2f v) const;

            /// \brief Returns the angle in degrees of 2 normalized vectors
            float calculateDegrees(const vec2f normalizedVector1, const vec2f normalizedVector2) const;
    };
}

#endif // TAGENGINE_H
