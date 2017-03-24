#include "tag/EMesh.h"

tag::EMesh::EMesh() :
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
        m_mesh->draw();
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

//////////////////
tag::vec3f tag::EMesh::getBoundingBox()
{
    if (m_mesh)
        return m_mesh->getBoundingBox();
    else
        return vec3f(0,0,0);
}
