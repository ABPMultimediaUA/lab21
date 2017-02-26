#include "tag/ResourceMesh.h"

#include <stdio.h>
#include <iostream>
#include <stdexcept>


#include "tag/Entity.h"
#include "tag/TAGEngine.h"
#include "tag/Types.h"


#include <glm/gtc/matrix_transform.hpp>


tag::ResourceMesh::ResourceMesh() :
    m_vertices(0),
    m_normals(0),
    m_textUV(0),
    m_verticesIndex(0),
    m_normalsIndex(0),
    m_textUVIndex(0),
    m_numVertices(0)
{
    //ctor
}

tag::ResourceMesh::~ResourceMesh()
{
    //dtor
    delete[] m_vertices;
    delete[] m_normals;
    delete[] m_textUV;
    delete[] m_verticesIndex;
    delete[] m_normalsIndex;
    delete[] m_textUVIndex;
    delete[] m_color;
}

void tag::ResourceMesh::aiVector3DToArrayGLFloat(const aiVector3D &source, GLfloat* dest)
{
    dest[0] = source.x;
    dest[1] = source.y;
    dest[2] = source.z;
}

void tag::ResourceMesh::load(std::string fileName)
{
    setName(fileName);

    // No hacer un delete de aiScene, ya se encarga Assimp de dejarlo todo limpito
    // aiProcess_Triangulate: totalmente necesario. Asumimos 3 caras por vertice.
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

    unsigned int vertices = scene->mMeshes[0]->mNumVertices;
    m_vertices    = new GLfloat[vertices*3];
    m_normals     = new GLfloat[vertices*3];
    m_textUV      = new GLfloat[vertices*3];
    for(unsigned int i=0; i<vertices; i++)
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

    m_numVertices = scene->mMeshes[0]->mNumFaces * 3;
    m_verticesIndex = new GLuint[m_numVertices];
    m_normalsIndex  = new GLuint[m_numVertices];
    m_textUVIndex   = new GLuint[m_numVertices];

    unsigned int indicesCount = 0;
    for(unsigned int i=0; i<scene->mMeshes[0]->mNumFaces; i++)
    {
        for(unsigned int j=0; j<scene->mMeshes[0]->mFaces[i].mNumIndices && indicesCount<m_numVertices; j++)
        {
            m_verticesIndex[indicesCount] = scene->mMeshes[0]->mFaces[i].mIndices[j];
            indicesCount++;
        }
    }
    // TODO el color
    m_color = new GLfloat[4];
    m_color[0] = 1.0;
    m_color[1] = 0.5;
    m_color[2] = 0.5;
    m_color[3] = 1.0;
}

void tag::ResourceMesh::draw(vec3f position, vec3f rotation)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;


    //////////////////////////
    // TODO el cálculo de la posición y la rotación (modelview) no irá aqui.
    // Cálculo de la ModelView
    modelMatrix     = glm::mat4(1.0f); // matriz identidad
    // Aplicamos posicion
    modelMatrix     = glm::translate(modelMatrix, glm::vec3(position.x, position.y, position.z));
    // Aplicamos rotacion
    modelMatrix     = glm::rotate(modelMatrix, rotation.x, glm::vec3(1,0,0));
    modelMatrix     = glm::rotate(modelMatrix, rotation.y, glm::vec3(0,1,0));
    modelMatrix     = glm::rotate(modelMatrix, rotation.z, glm::vec3(0,0,1));
    modelViewMatrix = Entity::MVmatrix * modelMatrix;
    ///////////////////////////


    // Envía nuestra ModelView al Vertex Shader
    glUniformMatrix4fv(TAGEngine::m_uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

    // Pintar
    glUniform4fv(TAGEngine::m_uColorLocation, 1, m_color);

    // Asociamos los vértices y sus normales
    glVertexAttribPointer(TAGEngine::m_aPositionLocation, 3, GL_FLOAT, false, sizeof(GLfloat)*3, m_vertices);
    glVertexAttribPointer(TAGEngine::m_aNormalLocation, 3, GL_FLOAT, false, sizeof(GLfloat)*3, m_normals);

    glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, m_verticesIndex);
}







