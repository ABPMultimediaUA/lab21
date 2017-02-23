#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#include "Resource.h"
#include <SFML/OpenGL.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace dwe
{
    class ResourceMesh : public Resource
    {
        public:
            ResourceMesh();
            virtual ~ResourceMesh();

            void load(std::string fileName);
            void draw();

        private:
            GLfloat* m_vertex;
            GLfloat* m_normals;
            GLfloat* m_textUV;

            GLuint* m_vertexIndex;
            GLuint* m_normalsIndex;
            GLuint* m_textUVIndex;

            unsigned int m_numVertex;
    };
}

#endif // RESOURCEMESH_H
