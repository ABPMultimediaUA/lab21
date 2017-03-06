#ifndef TAGENGINE_H
#define TAGENGINE_H

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define MAX_MESSAGE_LINES 4

// Nombre de los attributes
#define A_POSITION  "a_Position"
#define A_NORMAL    "a_Normal"

// Nombre de los uniforms
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_VMATRIX               "u_VMatrix"
#define U_COLOR                 "u_Color"
#define U_LUZ0                  "u_Luz0"


#define GLEW_STATIC
#include<GL/glew.h>

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "tag/Types.h"
#include "tag/GraphicNode.h"
#include "tag/EMesh.h"


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
            /// \details Debe ser llamado antes de cualquier otra función del motor.
            void init();

            /// \brief Comprueba que la ventana esté abierta y obtiene los mensajes de la misma.
            /// \details Debe ser llamado antes de dibujar, en cada iteración del bucle.
            /// Obtiene los mensajes de cerrar ventana, maximizar... y los de teclado/ratón.
            /// \return true si la ventana no ha sido cerrada.
            bool isRunning();

            /// \brief Realiza el dibujado de los nodos.
            /// \details Limpia la ventana openGL, prepara los parámetros de los shaders, las matrices
            /// dibuja los nodos y muestra los fps.
            void draw();

            /// \brief Crea una malla en el arbol.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotación. Crea
            /// el nodo Mesh y le asocia un ResourceMesh con la malla cargada mediante el
            /// ResourceManager.
            /// \param[in] fileName Nombre del fichero que contiene la malla
            /// \param[in] position Posición. Creará un nodo Transform con esos valores
            /// \param[in] rotation Rotación. Creará un nodo Transform con esos valores
            /// \param[in] parent Nodo padre. Si es 0 se le asignará el root.
            /// \return puntero al nodo de la malla creada
            GraphicNode* createMesh(const std::string fileName, const vec3f position, const vec3f rotation, GraphicNode* parent=0);


            /// \brief Crea una cámara de perspectiva en el arbol.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotación. Crea
            /// el nodo ECamera y le asigna los parametros de Perspectiva. Si es la primera cámara que
            /// se crea (si m_numActiveCamera es cero, no hay ninguna activa) llama a setActiveCamera() con la nueva creada.
            /// \param[in] position Posición. Creará un nodo Transform con esos valores
            /// \param[in] rotation Rotación. Creará un nodo Transform con esos valores
            /// \param[in] fov, aspect, near, far Parámetros para la cámara de perspectiva.
            /// \param[in] parent Nodo padre. Si es 0 se le asignará el root.
            /// \return puntero al nodo de la cámara creada
            GraphicNode* createPerspectiveCamera(const vec3f position, const vec3f rotation, float fov, float aspect, float near, float far, GraphicNode* parent=0);


            /// \brief Establece la cámara activa. 0 ninguna cámara activa, 1 primera cámara...
            /// \details Cuando se establece la cámara activa se recalculan las transformaciones de la cámara
            /// y se establece la Entity::viewMatrix.
            void setActiveCamera(const unsigned int activeCamera);

            /***/
            GraphicNode* createLight(const vec3f position, const vec3f rotation, GraphicNode* parent=0);

            void setLightOn(const unsigned int light);

            // Handles de los attributes y uniforms
            static int m_aPositionLocation;
            static int m_aNormalLocation;
            static int m_uProjectionMatrixLocation;
            static int m_uMVMatrixLocation;
            static int m_uVMatrixLocation;
            static int m_uColorLocation;
            static int m_uLuz0Location;

            static const float screenHeight = 600;
            static const float screenWidth  = 800;

        private:
            sf::RenderWindow*   m_window;
            Program*            m_shaderProgram;

            sf::Clock           m_clock;
            float               m_secondsLastDraw;

            sf::Font            m_font;
            sf::Text            m_messageLine[MAX_MESSAGE_LINES];

            GraphicNode                 m_rootNode;
            std::vector<GraphicNode*>   m_lights;
            std::vector<GraphicNode*>   m_cameras;
            unsigned int                m_numActiveCamera;

            glm::mat4 m_projectionMatrix; // Almacena la matriz de proyección

            void renderElements();

            GraphicNode* createNodeTransform(GraphicNode* parent);
            GraphicNode* createNodeRotation(const vec3f rotation, GraphicNode* parent);
            GraphicNode* createNodePosition(const vec3f position, GraphicNode* parent);
    };
}

#endif // TAGENGINE_H
