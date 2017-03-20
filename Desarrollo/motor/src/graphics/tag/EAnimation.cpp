#include "tag/EAnimation.h"
#include <sstream>
#include <iostream>

tag::EAnimation::EAnimation() :
    m_animations(0), m_numAnimation(0), m_frame(0), temp(0)
{
    //ctor
}

tag::EAnimation::~EAnimation()
{
    //dtor
}

/////////////////
void tag::EAnimation::beginDraw(/*int animation, int frame*/)
{

    if (m_animations!=0)
        //aqui hariamos el bucle empezando por el frame 0
        m_animations[getNumAnimation()][m_frame]->draw();
        temp++;
        if(temp==60){

            m_frame++;
            temp=0;
        }
        if(m_frame==9)
            m_frame=0;

}

////////////////////////
void tag::EAnimation::endDraw()
{

}

////////////////////////

void tag::EAnimation::createNumAnimations(int numAnimations){
    m_animations = new ResourceMesh**[numAnimations];
}

////////////////////////
void tag::EAnimation::createAnimation(int numAnimation, int numFrames, std::string fileName){



    m_animations[numAnimation] = new ResourceMesh*[numFrames]; //tamanyo de la animacion(numero de frames o meshes)
    for(int i=0; i<numFrames; i++)
    {
        std::stringstream ss;
        std::string s;
        ss << i;
        s = ss.str();
        std::string file=fileName+s+".obj";
        m_animations[numAnimation][i] = static_cast<ResourceMesh*>(Entity::resourceManager.getResource(file));

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

