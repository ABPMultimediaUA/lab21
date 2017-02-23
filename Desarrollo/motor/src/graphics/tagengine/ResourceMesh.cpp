#include "ResourceMesh.h"

#include <stdio.h>
#include <iostream>
#include <stdexcept>


dwe::ResourceMesh::ResourceMesh() :
    m_vertex(0),
    m_normals(0),
    m_textUV(0),
    m_vertexIndex(0),
    m_normalsIndex(0),
    m_textUVIndex(0),
    m_numVertex(0)
{
    //ctor
}

dwe::ResourceMesh::~ResourceMesh()
{
    //dtor
    delete[] m_vertex;
    delete[] m_normals;
    delete[] m_textUV;
    delete[] m_vertexIndex;
    delete[] m_normalsIndex;
    delete[] m_textUVIndex;
}


void dwe::ResourceMesh::load(std::string fileName)
{
    std::cout <<"load\n";
    setName(fileName);

    Assimp::Importer importer;
    // No hacer un delete, ya se encarga Assimp de dejarlo todo limpito
    // aiProcess_Triangulate: totalmente necesario. Asumimos 3 caras por vertice.
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

    m_numVertex = scene->mMeshes[0]->mNumVertices;
    m_vertex  = new GLfloat[m_numVertex*3];
    m_normals = new GLfloat[m_numVertex*3];
    m_textUV  = new GLfloat[m_numVertex*3];
    for(unsigned int i=0; i<m_numVertex; i++)
    {
        int j = i*3;

        m_vertex[j+0] = scene->mMeshes[0]->mVertices[i].x;
        m_vertex[j+1] = scene->mMeshes[0]->mVertices[i].y;
        m_vertex[j+2] = scene->mMeshes[0]->mVertices[i].z;

        if (scene->mMeshes[0]->HasNormals())
        {
            m_normals[j+0] = scene->mMeshes[0]->mNormals[i].x;
            m_normals[j+1] = scene->mMeshes[0]->mNormals[i].y;
            m_normals[j+2] = scene->mMeshes[0]->mNormals[i].z;
        }

        // TODO ¿por que utiliza x,y,z, no se supone que son valores u,v entre 0 y 1???
        if (scene->mMeshes[0]->HasTextureCoords(0))
        {
            // mTextureCoords es un array de dos dimensiones, la primera la textura (asumimos solo una)
            // se supone que z no se usa, y se guardan los valores u,v en x,y, la z es por si hay componente w
            m_textUV[j+0] = scene->mMeshes[0]->mTextureCoords[0][i].x;
            m_textUV[j+1] = scene->mMeshes[0]->mTextureCoords[0][i].y;
            m_textUV[j+2] = scene->mMeshes[0]->mTextureCoords[0][i].z;
        }
    }

    // Al tener aiProcess_Triangulate sabemos que son 3 vertices por cara
    unsigned int maxIndices = scene->mMeshes[0]->mNumFaces * 3;
    m_vertexIndex  = new GLuint[maxIndices];
    m_normalsIndex = new GLuint[maxIndices];
    m_textUVIndex  = new GLuint[maxIndices];

    unsigned int indicesCount=0;
    for(unsigned int i=0; i<scene->mMeshes[0]->mNumFaces; i++)
    {
        for(unsigned int j=0; j<scene->mMeshes[0]->mFaces[i].mNumIndices && indicesCount<maxIndices; j++)
        {
            m_vertexIndex[indicesCount] = scene->mMeshes[0]->mFaces[i].mIndices[j];
            indicesCount++;
        }
    }
}

void dwe::ResourceMesh::draw()
{

}







