#include "tag/EMesh.h"

tag::EMesh::EMesh() :
    m_texture(0),
    m_mesh(0)
{
    //ctor
}

tag::EMesh::~EMesh()
{
    //dtor
}

/////////////////
void tag::EMesh::beginDraw()
{
    if (m_mesh!=0)
    {
        if (m_texture)
            m_texture->activateTexture();
        else
            ResourceTexture::_deactivateTexture();

        m_mesh->draw();

        if (m_texture)
            ResourceTexture::_deactivateTexture();
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
