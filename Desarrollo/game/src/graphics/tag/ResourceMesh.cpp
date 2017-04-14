#include "tag/ResourceMesh.h"

#include <stdio.h>
#include <stdexcept>
#include <iostream>


#include "tag/Entity.h"
#include "tag/TAGEngine.h"
#include "tag/Types.h"
#include "tag/TAGError.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


tag::ResourceMesh::ResourceMesh() :
    m_vertices(0),
    m_normals(0),
    m_textUV(0),
    m_indices(0),
    m_numVertices(0),
    m_vbVertices(0),
    m_vbNormals(0),
    m_vbTextUV(0),
    m_ibVertices(0)
{
    //ctor
}

tag::ResourceMesh::~ResourceMesh()
{
    //dtor
    delete[] m_vertices;
    delete[] m_normals;
    delete[] m_textUV;
    delete[] m_indices;
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
    glDeleteBuffers(1, &m_vbNormals);
    glDeleteBuffers(1, &m_vbTextUV);
    glDeleteBuffers(1, &m_ibVertices);
}

void tag::ResourceMesh::createOpenGLBuffers()
{
    glGenBuffers(1, &m_vbVertices);
    glGenBuffers(1, &m_vbNormals);
    glGenBuffers(1, &m_vbTextUV);
    glGenBuffers(1, &m_ibVertices);
}

void tag::ResourceMesh::unsetBuffers()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void tag::ResourceMesh::prepareOpenGLBuffers()
{
    deleteOpenGLBuffers();
    createOpenGLBuffers();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m_numVertices*3, m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbNormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m_numVertices*3, m_normals, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbTextUV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m_numVertices*3, m_textUV, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibVertices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_numIndices, m_indices, GL_STATIC_DRAW);

    unsetBuffers();
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
    m_indices = new GLuint[m_numIndices];

    unsigned int indicesCount = 0;
    for(unsigned int i=0; i<scene->mMeshes[0]->mNumFaces; i++)
    {
        for(unsigned int j=0; j<scene->mMeshes[0]->mFaces[i].mNumIndices && indicesCount<m_numIndices; j++)
        {
            m_indices[indicesCount] = scene->mMeshes[0]->mFaces[i].mIndices[j];
            indicesCount++;
        }
    }

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

    calculateBoundingBox();
}

void tag::ResourceMesh::draw()
{
    glm::mat4 modelViewMatrix;
    glm::mat4 mvpMatrix;
    glm::mat3 normalMatrix;

    normalMatrix = glm::mat3(glm::transpose(glm::inverse(Entity::modelMatrix)));

    modelViewMatrix = Entity::viewMatrix * Entity::modelMatrix;
    mvpMatrix = Entity::projectionMatrix * modelViewMatrix;

    // Envía nuestra ModelView al Vertex Shader
    glUniformMatrix4fv(TAGEngine::_uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

    // Envía matriz MVP al Vertex Shader
    glUniformMatrix4fv(TAGEngine::_uMVPLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

    // Envía NormalMatrix Vertex Shader
    glUniformMatrix3fv(TAGEngine::_uNormalMatrixLocation, 1, GL_FALSE, &normalMatrix[0][0]);

    // Asociamos los vértices y sus normales
    glBindBuffer(GL_ARRAY_BUFFER, m_vbVertices);
    glVertexAttribPointer(TAGEngine::_aVertexPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbNormals);
    glVertexAttribPointer(TAGEngine::_aVertexNormalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbTextUV);
    glVertexAttribPointer(TAGEngine::_aTextureCoordsLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

    // Dibjuamos elementos
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibVertices);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
}

void tag::ResourceMesh::calculateBoundingBox()
{
    vec3f mins;
    vec3f maxs;

    maxs = mins = vec3f(m_vertices[0], m_vertices[1], m_vertices[2]);

    for (size_t i=1; i<m_numVertices; i++)
    {
        size_t j=i*3;

        if (mins.x > m_vertices[j]) mins.x = m_vertices[j];
        else if (maxs.x < m_vertices[j]) maxs.x = m_vertices[j];

        if (mins.y > m_vertices[j+1]) mins.y = m_vertices[j+1];
        else if (maxs.y < m_vertices[j+1]) maxs.y = m_vertices[j+1];

        if (mins.z > m_vertices[j+2]) mins.z = m_vertices[j+2];
        else if (maxs.z < m_vertices[j+2]) maxs.z = m_vertices[j+2];
    }

    m_boundingBox = vec3f(maxs.x - mins.x,  maxs.y - mins.y,  maxs.z - mins.z);
}


tag::vec3f tag::ResourceMesh::getBoundingBox()
{
    return m_boundingBox;
}





