#include "tag/EAnimation.h"
#include <sstream>
#include <iostream>

tag::EAnimation::EAnimation() :
    m_numAnimation(0), m_frame(0), temp(0), m_animations(0)
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
    if (m_animations!=0)
        //aqui hariamos el bucle empezando por el frame 0
        m_animations[getNumAnimation()].frames[m_frame]->draw();
        temp++;
        if(temp == 30){

            m_frame++;
            temp = 0;
        }
        if(m_frame == m_animations[getNumAnimation()].numFrames)
            m_frame=0;

}

////////////////////////
void tag::EAnimation::endDraw()
{

}

////////////////////////
void tag::EAnimation::createNumAnimations(int numAnimations){
    m_animations = new TAnimation[numAnimations];
}

////////////////////////
void tag::EAnimation::createAnimation(int numAnimation, int numFrames, std::string fileName){

    m_animations[numAnimation].frames = new ResourceMesh*[numFrames]; //tamanyo de la animacion(numero de frames o meshes)
    m_animations[numAnimation].numFrames = numFrames;//ponemos el numero de frames de la animacion
    for(int i=0; i<numFrames; i++)
    {
        std::stringstream ss;
        std::string s;
        ss << i;
        s = ss.str();
        std::string file=fileName+s+".obj";
        m_animations[numAnimation].frames[i] = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(file));

    }
}


////////////////////////
void tag::EAnimation::setNumAnimation(int animation)
{
    m_numAnimation = animation;
}
////////////////////////
int tag::EAnimation::getNumAnimation()
{
    return m_numAnimation;
}

tag::vec3f tag::EAnimation::getBoundingBox()
{
    if (m_animations)
        return m_animations[getNumAnimation()].frames[0]->getBoundingBox();
    else
        return vec3f(0,0,0);
}
