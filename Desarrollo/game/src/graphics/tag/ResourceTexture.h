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

            virtual void load(std::string fileName);

            void activateTexture() const;
            static void _deactivateTexture();

        protected:

        private:
            GLushort* m_image;
            GLuint    m_textureID;

            GLuint loadTexture(Image* image);
    };
}

#endif // TAG_RESOURCETEXTURE_H
