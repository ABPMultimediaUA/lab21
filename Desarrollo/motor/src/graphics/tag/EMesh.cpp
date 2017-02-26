#include "tag/EMesh.h"

#include <iostream>

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
void tag::EMesh::loadMesh(char *file)
{
    std::cout << "Cargando malla " << file << std::endl;
}
