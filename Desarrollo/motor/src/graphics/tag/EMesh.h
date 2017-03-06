#ifndef EMESH_H
#define EMESH_H

#include "Entity.h"
#include "ResourceMesh.h"


namespace tag
{
    class EMesh : public Entity
    {
        public:
            EMesh();
            ~EMesh();

            /// \brief Carga una malla desde un fichero usando ResourceManager
            /// \details Si ese nombre de malla ha sido cargado previamente, ResourceManager no
            /// cargará una nueva, sino que asignará el puntero de la misma a m_mesh
            void loadMesh(std::string fileName);

            void beginDraw();
            void endDraw();

        private:
            ResourceMesh* m_mesh;
    };
}

#endif // EMESH_H
