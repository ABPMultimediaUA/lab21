#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#define GLEW_STATIC
#include<GL/glew.h>

#include "Resource.h"
#include <SFML/OpenGL.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "tag/Types.h"



namespace tag
{
    class ResourceMesh : public Resource
    {
        public:
            ResourceMesh();
            virtual ~ResourceMesh();

            virtual void load(std::string fileName);

            void draw();

        private:
            GLfloat *m_vertices;
            GLfloat *m_normals;
            GLfloat *m_textUV;
            GLfloat *m_color;

            GLuint *m_verticesIndices;
            GLuint *m_normalsIndices;
            GLuint *m_textUVIndices;

            GLuint m_numVertices;
            GLuint m_numIndices;

            GLuint m_vbVertices;
            GLuint m_ibVertices;
            GLuint m_vbNormals;
            GLuint m_ibNormals;

            void aiVector3DToArrayGLFloat(const aiVector3D &source, GLfloat* dest);
            void aiSceneToOpenGLMesh(const aiScene* scene);
            void prepareOpenGLBuffers();
            void createOpenGLBuffers();
            void deleteOpenGLBuffers();
    };
}

#endif // RESOURCEMESH_H
