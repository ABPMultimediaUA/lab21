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
            void createNumAnimations(uint8_t numAnimations);//creamos el array pasandole un numero de animaciones q tendra
            void createAnimation(uint8_t animationIndex, uint8_t numFrames, std::string fileName, bool loop = true);//creamos la animacion dentro del array(en una posicion), con el numero de frames que tendra
            void setActiveAnimation(uint8_t animationIndex);//establecemos en que animation estamos para el draw
            uint8_t getActiveAnimation();//devolvemos en que animation estamos para el draw

            vec3f getBoundingBox();

        private:
            uint8_t m_activeAnimation;
            uint8_t m_numAnimations;
            uint8_t m_frame;
            uint8_t temp;
            struct TAnimation{
                uint8_t numFrames;
                bool    loop;
                ResourceMesh **frames;
            };
            TAnimation *m_animations;
    };
}

#endif // TAG_EANIMATION_H

