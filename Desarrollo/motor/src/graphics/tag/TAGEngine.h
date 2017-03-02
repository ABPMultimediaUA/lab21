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

            // TODO quitar. Funciónes provisionales que crean un nodo con el cubo para dibujarlo en renderElements
            void createNode();
            void createNode2();


            // Handles de los attributes y uniforms
            static int m_aPositionLocation;
            static int m_aNormalLocation;
            static int m_uProjectionMatrixLocation;
            static int m_uMVMatrixLocation;
            static int m_uVMatrixLocation;
            static int m_uColorLocation;
            static int m_uLuz0Location;


            ResourceManager getResourceManager(); //f

        private:
            sf::RenderWindow*   m_window;
            Program*            m_shaderProgram;

            sf::Clock           m_clock;
            float               m_secondsLastDraw;

            sf::Font            m_font;
            sf::Text            m_messageLine[MAX_MESSAGE_LINES];

            ResourceManager     m_resourceManager;

            ResourceMesh* resourceMesh;  // TODO quitar. Provisional para mostrar un cubo en renderElements
            ResourceMesh* resourceMesh2;  // TODO quitar. Provisional para mostrar un cubo en renderElements

            glm::mat4 m_projectionMatrix; // Almacena la matriz de proyección

            void renderElements();
    };
}

#endif // TAGENGINE_H
