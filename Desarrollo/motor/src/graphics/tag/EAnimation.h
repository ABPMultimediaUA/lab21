#ifndef EANIMATION_H
#define EANIMATION_H

#include "Entity.h"
#include "ResourceMesh.h"

namespace tag
{
    class EAnimation : public Entity
    {
        public:
            EAnimation();
            ~EAnimation();

            //cargamos la malla y el frame en el que estara

            void beginDraw(/*int animation, int frame*/);//dibujaremos a partir de la animacion y su frame
            void endDraw();
            void createNumAnimations(int numAnimations);//creamos el array pasandole un numero de animaciones q tendra
            void createAnimation(int numAnimation, int numFrames, std::string fileName);//creamos la animacion dentro del array(en una posicion), con el numero de frames que tendra
            void setNumAnimation(int animation);//establecemos en que animation estamos para el draw
            int getNumAnimation();//devolvemos en que animation estamos para el draw

        private:
            //ResourceMesh ***m_animations;//va a ser el array de animaciones
            int m_numAnimation;
            int m_frame;
            int temp;
            //int *m_animationFrames;//para saber cuantos frames tiene cada animacion
            struct TAnimation{
                int numFrames;
                ResourceMesh **frames;
            };
            TAnimation *m_animations;
    };
}

#endif // EANIMATION_H

