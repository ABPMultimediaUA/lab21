...

namespace tag
{
    class TAGEngine
    {
        public:

            ...

            /// \brief Crea un array de animaciones.
            /// \param[in] numAnimations Numero de animaciones que tendra el array
            /// \return array de la animación
            EAnimation* createNumAnimations(int numAnimations);

            /// \brief Crea una animacion.
            /// \details Crea una animación en una posición del array con el número de mallas que tiene, leyéndolas
            /// de un archivo al que se le sumará el número del frame (ej: andando i+1.obj, andando i+2.obj)
            /// \param[in] animations Array que contiene a las animaciones
            /// \param[in] fileName El nombre del archivo sobre el que iterará para coger todos los obj.
            /// \param[in] numAnimation Posición de la animación en el array de animaciones.
            /// \param[in] numFrames Número de frames que tendrá la animación. Número de mallas.
            /// \return puntero al nodo de la malla creada
            EAnimation* createAnimation(EAnimation* animations, const std::string fileName, int numAnimation, int numFrames);

            /// \brief Crea el nodo del array de animaciones.
            /// \details Crea los nodos de transformacion, uno de posicion y otro de rotación. Crea
            /// el nodo nodoAnimation y le asocia el array de animaciones.
            /// \param[in] animations Array que contiene a las animaciones
            /// \param[in] position Posición. Creará un nodo Transform con esos valores
            /// \param[in] rotation Rotación. Creará un nodo Transform con esos valores
            /// \param[in] parent Nodo padre. Si es 0 se le asignará el root.
            /// \return puntero al nodo del array de array de mallas.
            GraphicNode* createNodeAnimations(EAnimation* animations, const vec3f position, const vec3f rotation, GraphicNode* parent=0);

            ...
           
    };
}

#endif // TAGENGINE_H
