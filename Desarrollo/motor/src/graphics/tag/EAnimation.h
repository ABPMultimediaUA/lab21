#ifndef EANIMATION_H
#define EANIMATION_H

#include "Entity.h"
#include "ResourceManager.h"
#include "ResourceMesh.h"
#include "TAGEngine.h"


namespace tag
{
    class EAnimation : public Entity
    {
        public:
            EAnimation();
            ~EAnimation();

            void loadFrame(std::string fileName, int frame);//cargamos frame a frame

            void beginDraw();
            void endDraw();
            ResourceMesh* getFrame(int i);//devuelve un frame
            void setFrame(int j, ResourceMesh* resource);//devuelve un frame
        private:
            ResourceMesh* m_animation[2];//por poner un numero
            ResourceManager* resourceManager; //
    };
}

#endif // EANIMATION_H

