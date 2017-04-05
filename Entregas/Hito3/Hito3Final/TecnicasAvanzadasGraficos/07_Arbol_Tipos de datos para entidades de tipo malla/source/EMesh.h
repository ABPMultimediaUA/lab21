#ifndef TAG_EMESH_H
#define TAG_EMESH_H

#include "tag/Entity.h"
#include "tag/ResourceMesh.h"
#include "tag/ResourceTexture.h"


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

            /// \brief Carga una imagen de textura desde un fichero usando ResourceManager
            /// \details Si ese nombre de fichero ha sido cargado previamente, ResourceManager no
            /// cargará una nueva, sino que asignará el puntero de la misma a m_texture
            void loadTexture(std::string fileName);

            /// \brief Activa la textura m_texture si existe, dibuja m_mesh y desactiva la textura
            void beginDraw();

            void endDraw();
            vec3f getBoundingBox();

        private:
            ResourceTexture*    m_texture;
            ResourceMesh*       m_mesh;
    };
}

#endif // TAG_EMESH_H
