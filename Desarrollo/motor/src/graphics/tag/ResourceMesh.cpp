#include "tag/ResourceMesh.h"

#include <stdio.h>
#include <stdexcept>
#include <iostream>


#include "tag/Entity.h"
#include "tag/TAGEngine.h"
#include "tag/Types.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


tag::ResourceMesh::ResourceMesh() :
    m_vertices(0),
    m_normals(0),
    m_textUV(0),
    m_verticesIndices(0),
    m_normalsIndices(0),
    m_textUVIndices(0),
    m_numVertices(0),
    m_vbVertices(0),
    m_ibVertices(0),
    m_vbNormals(0),
    m_ibNormals(0)
{
    //ctor
}

tag::ResourceMesh::~ResourceMesh()
{
    //dtor
    delete[] m_vertices;
    delete[] m_normals;
    delete[] m_textUV;
    delete[] m_verticesIndices;
    delete[] m_normalsIndices;
    delete[] m_textUVIndices;
    delete[] m_color;
}

void tag::ResourceMesh::aiVector3DToArrayGLFloat(const aiVector3D &source, GLfloat* dest)
{
    dest[0] = source.x;
    dest[1] = source.y;
    dest[2] = source.z;
}

void tag::ResourceMesh::deleteOpenGLBuffers()
{
    glDeleteBuffers(1, &m_vbVertices);
    glDeleteBuffers(1, &m_ibVertices);

    glDeleteBuffers(1, &m_vbNormals);
    glDeleteBuffers(1, &m_ibNormals);
}

void tag::ResourceMesh::createOpenGLBuffers()
{
    glGenBuffers(1, &m_vbVertices);
    glGenBuffers(1, &m_ibVertices);

    glGenBuffers(1, &m_vbNormals);
    glGenBuffers(1, &m_ibNormals);
}

void tag::ResourceMesh::prepareOpenGLBuffers()
{
    deleteOpenGLBuffers();
    createOpenGLBuffers();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m_numVertices*3, m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbNormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m_numVertices*3, m_normals, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibVertices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_numIndices, m_verticesIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void tag::ResourceMesh::aiSceneToOpenGLMesh(const aiScene* scene)
{
    m_numVertices = scene->mMeshes[0]->mNumVertices;
    m_vertices    = new GLfloat[m_numVertices*3];
    m_normals     = new GLfloat[m_numVertices*3];
    m_textUV      = new GLfloat[m_numVertices*3];
    for(unsigned int i=0; i<m_numVertices; i++)
    {
        int j = i*3;

        aiVector3DToArrayGLFloat(scene->mMeshes[0]->mVertices[i], &m_vertices[j]);

        if (scene->mMeshes[0]->HasNormals())
            aiVector3DToArrayGLFloat(scene->mMeshes[0]->mNormals[i], &m_normals[j]);

        // mTextureCoords es un array de dos dimensiones, la primera la textura (asumimos solo una)
        // se supone que z no se usa, y se guardan los valores u,v en x,y, la z es por si hay componente w
        if (scene->mMeshes[0]->HasTextureCoords(0))
            aiVector3DToArrayGLFloat(scene->mMeshes[0]->mTextureCoords[0][i], &m_textUV[j]);
    }

    m_numIndices = scene->mMeshes[0]->mNumFaces * 3;
    m_verticesIndices = new GLuint[m_numIndices];
    m_normalsIndices  = new GLuint[m_numIndices];
    m_textUVIndices   = new GLuint[m_numIndices];

    unsigned int indicesCount = 0;
    for(unsigned int i=0; i<scene->mMeshes[0]->mNumFaces; i++)
    {
        for(unsigned int j=0; j<scene->mMeshes[0]->mFaces[i].mNumIndices && indicesCount<m_numIndices; j++)
        {
            m_verticesIndices[indicesCount] = scene->mMeshes[0]->mFaces[i].mIndices[j];
            indicesCount++;
        }
    }
    // TODO el color
    m_color = new GLfloat[4];
    m_color[0] = 1.0;
    m_color[1] = 0.5;
    m_color[2] = 0.5;
    m_color[3] = 1.0;

    prepareOpenGLBuffers();
}

void tag::ResourceMesh::load(std::string fileName)
{
    setName(fileName);

    // No hacer un delete de aiScene, ya se encarga Assimp de dejarlo todo limpito
    // aiProcess_Triangulate: totalmente necesario. Asumimos 3 vertices por cara.
    Assimp::Importer importer;
    const aiScene* scene =  importer.ReadFile(fileName,
                                aiProcess_Triangulate            |
                                aiProcess_JoinIdenticalVertices  |
                                0
                            );
    if(!scene)
    {
        char msg[255];
        sprintf(msg, "Error cargando Malla: %s", importer.GetErrorString());
        throw std::runtime_error(msg);
    }

    aiSceneToOpenGLMesh(scene);
}

void tag::ResourceMesh::draw()
{
    glm::mat4   modelViewMatrix;

    modelViewMatrix = Entity::viewMatrix * Entity::modelMatrix;

    // Envía nuestra ModelView al Vertex Shader
    glUniformMatrix4fv(TAGEngine::m_uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

    // Color
    glUniform4fv(TAGEngine::m_uColorLocation, 1, m_color);

    // Asociamos los vértices y sus normales
    glBindBuffer(GL_ARRAY_BUFFER, m_vbVertices);
    glVertexAttribPointer(TAGEngine::m_aPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbNormals);
    glVertexAttribPointer(TAGEngine::m_aNormalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

    // Dibjuamos elementos
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibVertices);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
}







