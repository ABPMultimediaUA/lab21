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

void tag::EAnimation::createAnimation(int numAnimations){
    m_animations = new ResourceMesh**[numAnimations];
}

void tag::EAnimation::loadAnimation(std::string fileName, int animation, int frames)
{
    /*m_animations = new ResourceMesh**[2]; //array q debe ser el numero de animaciones q tenga el obj (podriamos definirlo al principio y asi solo pasariamos animacion a animacion)
    for(int i = 0; i < 3; i++){
        m_animations[i] = new ResourceMesh*[5]; //tamanyo de la animacion(numero de frames o meshes)
    }*/

    m_animations[animation] = new ResourceMesh*[frames]; //tamanyo de la animacion(numero de frames o meshes)
    for(int j = 0; j < frames; j++){
        m_animations[animation][j] = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(fileName));
    }

}
tag::ResourceMesh* tag::EAnimation::getFrame(int animation, int frame)
{
    return m_animations[animation][frame];
}
void tag::EAnimation::setFrame(int animation, int frame, ResourceMesh* resource)
{
   m_animations[animation][frame] = resource;
}


