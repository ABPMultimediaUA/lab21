#ifndef TAG_EMESH_H
#define TAG_EMESH_H

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
            vec3f getBoundingBox();

        private:
            ResourceMesh*   m_mesh;
    };
}

#endif // TAG_EMESH_H
