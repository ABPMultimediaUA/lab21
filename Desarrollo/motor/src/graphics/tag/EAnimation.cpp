#include "tag/EAnimation.h"

tag::EAnimation::EAnimation() :
    m_animations(0)
{
    //ctor
}

tag::EAnimation::~EAnimation()
{
    //dtor
}

/////////////////
void tag::EAnimation::beginDraw(int animation, int frame)
{
    if (m_animations!=0)
        m_animations[animation][frame]->draw();
}

/////////////////
void tag::EAnimation::endDraw()
{

}

/////////////////
void tag::EAnimation::loadAnimation(std::string fileName, int frames)
{
    m_animations = new ResourceMesh**[2]; //array de 3 animaciones
    for(int i = 0; i < 3; i++){
        m_animations[i] = new ResourceMesh*[5]; //tamanyo de la animacion
    }
    m_animations[0][0] = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(fileName));
    m_animations[0][1] = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(fileName));
    m_animations[0][2] = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(fileName));



}
tag::ResourceMesh* tag::EAnimation::getFrame(int animation, int frame)
{
    return m_animations[animation][frame];
}
void tag::EAnimation::setFrame(int animation, int frame, ResourceMesh* resource)
{
   m_animations[animation][frame] = resource;
}


