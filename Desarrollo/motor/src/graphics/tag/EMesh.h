#ifndef EMESH_H
#define EMESH_H

#include "Entity.h"
#include "ResourceManager.h"
#include "ResourceMesh.h"
#include "TAGEngine.h"


namespace tag
{
    class EMesh : public Entity
    {
        public:
            EMesh();
            ~EMesh();

            void loadMesh(std::string fileName);

            void beginDraw();
            void endDraw();

        private:

            ResourceMesh* m_mesh;
            ResourceManager* resourceManager; //
    };
}

#endif // EMESH_H
