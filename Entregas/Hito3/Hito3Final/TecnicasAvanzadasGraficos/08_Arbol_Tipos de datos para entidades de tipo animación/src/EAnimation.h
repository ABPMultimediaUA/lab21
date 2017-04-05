#ifndef TAG_EANIMATION_H
#define TAG_EANIMATION_H

#include "Entity.h"
#include "ResourceMesh.h"

namespace tag
{
    class EAnimation : public Entity
    {
        public:
            EAnimation();
            ~EAnimation();

            void beginDraw();
            void endDraw();
            void createNumAnimations(int numAnimations);//creamos el array pasandole un numero de animaciones q tendra
            void createAnimation(int numAnimation, int numFrames, std::string fileName);//creamos la animacion dentro del array(en una posicion), con el numero de frames que tendra
            void setNumAnimation(int animation);//establecemos en que animation estamos para el draw
            int getNumAnimation();//devolvemos en que animation estamos para el draw

            vec3f getBoundingBox() { return vec3f(0,0,0); };

        private:
            int m_numAnimation;
            int m_frame;
            int temp;
            struct TAnimation{
                int numFrames;
                ResourceMesh **frames;
            };
            TAnimation *m_animations;
    };
}

#endif // TAG_EANIMATION_H

