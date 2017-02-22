#include "EMesh.h"

#include <iostream>

dwe::EMesh::EMesh()
{
    //ctor
}

dwe::EMesh::~EMesh()
{
    //dtor
}

/////////////////
void dwe::EMesh::beginDraw()
{
    std::cout << "Begin " << m_cadena << "\n";
}

/////////////////
void dwe::EMesh::endDraw()
{
    std::cout << "End " << m_cadena << "\n";
}

/////////////////
void dwe::EMesh::loadMesh(char *file)
{
    std::cout << "Cargando malla " << file << std::endl;
}
