#ifndef TAG_RESOURCEMESH_H
#define TAG_RESOURCEMESH_H

#define GLEW_STATIC
#include<GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "tag/Resource.h"
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

            vec3f getBoundingBox();

        private:
            GLfloat *m_vertices;
            GLfloat *m_normals;
            GLfloat *m_textUV;
            GLfloat *m_color;

            GLuint *m_indices;

            GLuint m_numVertices;
            GLuint m_numIndices;

            GLuint m_vbVertices;
            GLuint m_vbNormals;
            GLuint m_vbTextUV;
            GLuint m_ibVertices;

            vec3f   m_boundingBox;

            void aiVector3DToArrayGLFloat(const aiVector3D &source, GLfloat* dest);
            void aiSceneToOpenGLMesh(const aiScene* scene);
            void prepareOpenGLBuffers();
            void createOpenGLBuffers();
            void deleteOpenGLBuffers();
            void calculateBoundingBox();
    };
}

#endif // TAG_RESOURCEMESH_H
