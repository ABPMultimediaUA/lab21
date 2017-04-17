#include "tag/EAnimation.h"
#include <sstream>
#include <iostream>

tag::EAnimation::EAnimation() :
    m_activeAnimation(0),
    m_numAnimations(0),
    m_frame(0),
    temp(0),
    m_animations(0)
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
        m_animations[m_activeAnimation].frames[m_frame]->draw();
        temp++;
        if(temp == 10)
        {
            m_frame++;
            temp = 0;

            if(m_frame >= m_animations[m_activeAnimation].numFrames)
            {
                if (m_animations[m_activeAnimation].loop)
                    m_frame=0;
                else
                    m_frame=m_animations[m_activeAnimation].numFrames-1;
            }
        }
}

////////////////////////
void tag::EAnimation::endDraw()
{

}

////////////////////////
void tag::EAnimation::createNumAnimations(uint8_t numAnimations){
    m_numAnimations = numAnimations;
    m_animations = new TAnimation[m_numAnimations];
}

////////////////////////
void tag::EAnimation::createAnimation(uint8_t animationIndex, uint8_t numFrames, std::string fileName, bool loop){

    m_animations[animationIndex].frames     = new ResourceMesh*[numFrames]; //tamanyo de la animacion(numero de frames o meshes)
    m_animations[animationIndex].numFrames  = numFrames;                    //ponemos el numero de frames de la animacion
    m_animations[animationIndex].loop       = loop;

    for(int i=0; i<numFrames; i++)
    {
        std::stringstream ss;
        std::string s;
        ss << i;
        s = ss.str();
        std::string file=fileName+s+".obj";
        m_animations[animationIndex].frames[i] = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(file));
    }
}

////////////////////////
void tag::EAnimation::setActiveAnimation(uint8_t animationIndex)
{
    if (animationIndex < m_numAnimations)
    {
        m_activeAnimation = animationIndex;
        m_frame = 0;
    }
}

/////////////////////////
uint8_t tag::EAnimation::getActiveAnimation()
{
    return m_activeAnimation;
}

tag::vec3f tag::EAnimation::getBoundingBox()
{
    if (m_animations)
        return m_animations[m_activeAnimation].frames[0]->getBoundingBox();
    else
        return vec3f(0,0,0);
}

