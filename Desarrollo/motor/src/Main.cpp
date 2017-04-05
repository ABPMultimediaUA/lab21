#define GLEW_STATIC
#include<GL/glew.h>

#include "Scene.h"
#include "GraphicsEngine.h"
#include "Player.h"
#include "Gun.h"


#include "tag/GraphicNode.h"
#include "tag/TAGEngine.h"


using namespace tag;

int main()
{
    GEInstance->init();

    GEInstance->createCamera();

    uint32_t i = 0;
    while (i<4000)
    {
        GEInstance->draw();
        i++;
    }

    return 0;
}
