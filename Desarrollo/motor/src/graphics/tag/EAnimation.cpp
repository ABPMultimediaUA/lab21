#include "tag/EAnimation.h"

#include <iostream>
#include "tag/ResourceManager.h"
#include "tag/ResourceMesh.h"
#include "tag/TAGEngine.h"
tag::EAnimation::EAnimation()
{
    //ctor
}

tag::EAnimation::~EAnimation()
{
    //dtor
}

/////////////////
void tag::EAnimation::beginDraw()
{
    std::cout << "Begin " << m_cadena << "\n";
}

/////////////////
void tag::EAnimation::endDraw()
{
    std::cout << "End " << m_cadena << "\n";
}

/////////////////
void tag::EAnimation::loadFrame(std::string fileName, int frame)
{
    std::cout << "Cargando malla animada " << fileName << std::endl;
    //m_animation[frame] = fileName; //metemos la malla en el frame

}
tag::ResourceMesh* tag::EAnimation::getFrame(int i)
{
    return m_animation[i];
}
void tag::EAnimation::setFrame(int j, ResourceMesh* resource)
{
    m_animation[j] = resource;
}


