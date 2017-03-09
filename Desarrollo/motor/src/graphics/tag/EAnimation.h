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

            void loadAnimation(std::string fileName, int frames);//cargamos la animacion y su numero de frames

            void beginDraw(int animation, int frame);//dibujaremos a partir de la animacion y su frame
            void endDraw();
            ResourceMesh* getFrame(int animation, int frame);//devuelve un mesh en una posicion de su animacion
            void setFrame(int animation, int frame, ResourceMesh* resource);//pasamos el numero de la animacion, el frame y el mesh
        private:
            ResourceMesh ***m_animations;//va a ser el array de animaciones
    };
}

#endif // EANIMATION_H

