#include "tag/EMesh.h"

tag::EMesh::EMesh() :
    m_texture(0),
    m_mesh(0)
{
    //ctor
}

tag::EMesh::~EMesh()
{
    if (m_texture)
    {
        delete m_texture;
        m_texture = 0;
    }
    if (m_mesh)
    {
        delete m_mesh;
        m_mesh = 0;
    }
}

/////////////////
void tag::EMesh::beginDraw()
{
    if (m_mesh)
    {
        if (m_texture)
        {
            m_texture->activateTexture();
            m_mesh->draw();
            m_texture->deactivateTexture();
        }
        else
        {
            m_mesh->draw();
        }
    }
}

/////////////////
void tag::EMesh::endDraw()
{
}

/////////////////
void tag::EMesh::loadMesh(std::string fileName)
{
    m_mesh = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(fileName));
}

/////////////////
void tag::EMesh::loadTexture(std::string fileName)
{
    m_texture = static_cast<ResourceTexture*>(Entity::resourceManager.getResource(fileName));
}

//////////////////
tag::vec3f tag::EMesh::getBoundingBox()
{
    if (m_mesh)
        return m_mesh->getBoundingBox();
    else
        return vec3f(0,0,0);
}
