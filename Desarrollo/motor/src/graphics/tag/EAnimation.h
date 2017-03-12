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

            void loadAnimation(std::string fileName, int animation, int frames);//animation sera el numero q ocupa la animacion en el array, y frames cuantos frames tiene
            //cargamos la animacion y su numero de frames
            //este metodo debemos pensar que queremos que haga exactamente: pasarle el numero de animaciones q tenga y cuanto
            //duran las animaciones(deberian medir todas lo mismo entonces), o pasarle animacion a animacion con su numero de
            //frames y la posicion de la animacion en el array

            void beginDraw(int animation, int frame);//dibujaremos a partir de la animacion y su frame
            void endDraw();
            void createAnimation(int numAnimations);//creamos el array pasandole un numero de animaciones q tendra
            ResourceMesh* getFrame(int animation, int frame);//devuelve un mesh en una posicion de su animacion
            void setFrame(int animation, int frame, ResourceMesh* resource);//pasamos el numero de la animacion, el frame y el mesh
        private:
            ResourceMesh ***m_animations;//va a ser el array de animaciones
    };
}

#endif // EANIMATION_H

