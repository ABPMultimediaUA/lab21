#ifndef EMESH_H
#define EMESH_H

#include "Entity.h"


namespace tag
{
    class EMesh : public Entity
    {
        public:
            EMesh();
            ~EMesh();

            void loadMesh(char *file);

            void beginDraw();
            void endDraw();
    };
}

#endif // EMESH_H
