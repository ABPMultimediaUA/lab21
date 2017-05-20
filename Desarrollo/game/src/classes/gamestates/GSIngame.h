#ifndef GSINGAME_H
#define GSINGAME_H

#include "GState.h"
#include "Game.h"
#include "Hud.h"

class GSIngame : public GState{
    public:
        GSIngame();
        ~GSIngame();
        void Init();

        void HandleEvents();
        void Update();
        void Render();
        static GSIngame* getInstance();
    private:
        int page;
        float timeStamp;
        float deltaTime;
        bool m;
        bool m_pausePermission; // Booleano para controlar el boton pausa
        bool m_clickPermission;
        Hud* hud;
};

#endif // GSINGAME_H
