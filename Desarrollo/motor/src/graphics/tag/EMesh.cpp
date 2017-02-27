#include "tag/EMesh.h"

#include <iostream>
#include "tag/ResourceManager.h"
#include "tag/ResourceMesh.h"
#include "tag/TAGEngine.h"
tag::EMesh::EMesh()
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
    std::cout << "Begin " << m_cadena << "\n";
}

/////////////////
void tag::EMesh::endDraw()
{
    std::cout << "End " << m_cadena << "\n";
}

/////////////////
void tag::EMesh::loadMesh(std::string fileName)
{
    std::cout << "Cargando malla " << fileName << std::endl;

    //m_mesh = static_cast<ResourceMesh*>(resourceManager->getResource(fileName));
}
