#ifndef TAG_RESOURCETEXTURE_H
#define TAG_RESOURCETEXTURE_H

#define GLEW_STATIC
#include<GL/glew.h>

#include "tag/Resource.h"
#include "tag/Types.h"

#include "loadBMP.h"

namespace tag
{
    class ResourceTexture : public Resource
    {
        public:
            ResourceTexture();
            virtual ~ResourceTexture();

            /// \brief Carga la textura
            virtual void load(std::string fileName);

            /// \brief Activa la textura cargada con load
            void activateTexture() const;

            /// \brief Desactiva la textura activa
            void deactivateTexture() const;

        protected:

        private:
            static unsigned int _nextTextureID;
            GLushort*           m_image;
            GLuint              m_textureID;
            unsigned int        m_textureIndex;

            GLuint loadTexture(Image* image);
    };
}

#endif // TAG_RESOURCETEXTURE_H
