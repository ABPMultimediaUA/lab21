...

namespace tag
{
    class TAGEngine
    {
        public:

            ...

            /// \brief Crea un array de animaciones.
            /// \param[in] numAnimations Numero de animaciones que tendra el array
            /// \return array de la animaci�n
            EAnimation* createNumAnimations(int numAnimations);

            /// \brief Crea una animacion.
            /// \details Crea una animaci�n en una posici�n del array con el n�mero de mallas que tiene, ley�ndolas
            /// de un archivo al que se le sumar� el n�mero del frame (ej: andando i+1.obj, andando i+2.obj)
            /// \param[in] animations Array que contiene a las animaciones
            /// \param[in] fileName El nombre del archivo sobre el que iterar� para coger todos los obj.
            /// \param[in] numAnimation Posici�n de la animaci�n en el array de animaciones.
            /// \param[in] numFrames N�mero de frames que tendr� la animaci�n. N�mero de mallas.
            /// \return puntero al nodo de la malla creada
            EAnimation* createAnimation(EAnimation* animations, const std::string fileName, int numAnimation, int numFrames);

            /// \brief Crea el nodo del array de animaciones.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotaci�n. Crea
            /// el nodo nodoAnimation y le asocia el array de animaciones.
            /// \param[in] animations Array que contiene a las animaciones
            /// \param[in] position Posici�n. Crear� un nodo Transform con esos valores
            /// \param[in] rotation Rotaci�n. Crear� un nodo Transform con esos valores
            /// \param[in] parent Nodo padre. Si es 0 se le asignar� el root.
            /// \return puntero al nodo del array de array de mallas.
            GraphicNode* createNodeAnimations(EAnimation* animations, const vec3f position, const vec3f rotation, GraphicNode* parent=0);

            ...
           
    };
}

#endif // TAGENGINE_H
