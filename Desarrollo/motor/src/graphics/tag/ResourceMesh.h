#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#define GLEW_STATIC
#include<GL/glew.h>

#include "Resource.h"
#include <SFML/OpenGL.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



namespace tag
{
    class ResourceMesh : public Resource
    {
        public:
            ResourceMesh();
            virtual ~ResourceMesh();

            void load(std::string fileName);
            void draw();

        private:
            GLfloat* m_vertices;
            GLfloat* m_normals;
            GLfloat* m_textUV;
            GLfloat* m_color;

            GLuint* m_verticesIndex;
            GLuint* m_normalsIndex;
            GLuint* m_textUVIndex;

            unsigned int m_numVertices;

            void aiVector3DToArrayGLFloat(const aiVector3D &source, GLfloat* dest);
    };
}

#endif // RESOURCEMESH_H
