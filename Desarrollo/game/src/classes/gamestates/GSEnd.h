#ifndef GSEND_H
#define GSEND_H

#include "GState.h"

namespace dwe
{
    class Button;
    class Background;
}

class GSEnd: public GState
{
    public:
        GSEnd();
        ~GSEnd();
        void Init();

        void HandleEvents();
        void Update();
        void Render();
        static GSEnd* getInstance();

    private:
        dwe::Background *endDemoBackground;
        bool ended;
};

#endif // GSEND_H
